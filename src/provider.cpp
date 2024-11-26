/**
 * This file provides gdb services by creating and controlling the connection with gdb.
 * 
 * This file has a C like implementation due to the original C implementation of this program.
 * 
 */



#include <sys/prctl.h>
#include "provider.h"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h> 

// C++
#include <string>

using namespace std;


gdb_proc* gdb_connect(string path)
{
	// This function was originally produced for a C program
	// It explains the use of malloc

    int* inpipefd, *outpipefd;
    gdb_proc* proc;

    // Allocations in heap
    inpipefd = (int*) malloc(sizeof(int) * 2);
    outpipefd = (int*) malloc(sizeof(int) * 2);
    proc = (gdb_proc*) malloc(sizeof(struct gdb_proc));

    // child pid
    pid_t pid = 0;

    if (pipe(inpipefd) != 0)  goto error;
    if (pipe(outpipefd) != 0) goto error;

	if (fcntl(inpipefd[0], F_SETFL, O_NONBLOCK) < 0) 
        goto error; 

    pid = fork();

    if (pid == -1) 
    {
      goto error;
    }
    else if (pid == 0) 
    {
		// Child process -> exec GDB

      	// Child
		dup2(outpipefd[0], STDIN_FILENO);
		dup2(inpipefd[1], STDOUT_FILENO);
		dup2(inpipefd[1], STDERR_FILENO);

		// ask kernel to deliver SIGTERM in case the parent dies
		prctl(PR_SET_PDEATHSIG, SIGTERM);

		//close unused pipe ends
		close(outpipefd[1]);
		close(inpipefd[0]);

		//replace tee with your process
		execl("/usr/bin/gdb", "gdb", path.c_str(), "--interpreter=mi4", "--silent", (char*) NULL);

		// Nothing below this line should be executed by child process. If so, 
		// it means that the execl function wasn't successfull, so lets exit:
		exit(1);

    } 
    else 
    {
		// MAIN process
		
		proc->pid = pid;
		proc->input_pipe  = inpipefd;
		proc->output_pipe = outpipefd;

		close(proc->output_pipe[0]);
		close(proc->input_pipe[1]);

		// We check that the fork process is still alive
		// before returning
		if (kill(proc->pid, 0) == 0) return proc;
		else goto error;

    }

    error:
    free(inpipefd);
    free(outpipefd);
    free(proc);
    return NULL;
}




/////////////////////////////////////////////////////////////////////////////





int gdb_send(struct gdb_proc *proc, char const* input)
{
	if (proc == NULL) return -1;
	else {
		return write(proc->output_pipe[1], input, strlen(input));
	}
}




/////////////////////////////////////////////////////////////////////////////





void gdb_read(struct gdb_proc *proc, string &fullBuff, std::mutex& m)
{
	char buf[1024];
	int n;

	while (1) {
		n=read(proc->input_pipe[0], buf, 1024);
		switch (n) {
			case -1:
				if (errno == EAGAIN) // End of the pipe
					break;
				else
					break;
			case 0:
				return ;
			default:
				// Lock to prevent from data race
				m.lock();
				fullBuff = fullBuff + buf;
				m.unlock();
		}
		// clear buffer
		memset(buf, 0, 1024);
	}

}



/////////////////////////////////////////////////////////////////////////////




void gdb_close(gdb_proc* proc) {

	if (kill(proc->pid, 0) == 0)
		kill(proc->pid, SIGKILL);

	close(proc->output_pipe[1]);
	close(proc->input_pipe[0]);

	free(proc->input_pipe);
	free(proc->output_pipe);
}