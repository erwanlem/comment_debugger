/*
#include <stdlib.h>
#include <sys/wait.h>

#include <string.h>
#include <sys/wait.h>


*/
#include <sys/prctl.h>
#include "provider.h"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>


/*

  // Now, you can write to outpipefd[1] and read from inpipefd[0] :  
  while(1)
  {

    /*printf("Enter message to send\n");
    scanf("%s", msg);
    if(strcmp(msg, "exit") == 0) break;
    
    write(outpipefd[1], "-break-insert 8\n", strlen("-break-insert 8\n"));
    write(outpipefd[1], "-break-commands 1 \"print n\" \"continue\"\n", strlen("-break-commands 1 \"print n\" \"continue\"\n"));
    write(outpipefd[1], "-exec-run\n", strlen("-exec-run\n"));
    write(outpipefd[1], "quit\n", strlen("quit\n"));


    while ((n=read(inpipefd[0], buf, 512))>0)
      printf("Received answer: %s\n", buf);

    memset(buf, 0, 512);
  }

  kill(pid, SIGKILL); //send SIGKILL signal to the child process
  waitpid(pid, &status, 0);
}
*/


struct gdb_proc* gdb_connect()
{
    int* inpipefd, *outpipefd;
    struct gdb_proc* proc;

    // Allocations in heap
    inpipefd = (int*) malloc(sizeof(int) * 2);
    outpipefd = (int*) malloc(sizeof(int) * 2);
    proc = (struct gdb_proc*) malloc(sizeof(struct gdb_proc));

    // child pid
    pid_t pid = 0;

    if (pipe(inpipefd) != 0)  goto error;
    if (pipe(outpipefd) != 0) goto error;

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

      //ask kernel to deliver SIGTERM in case the parent dies
      prctl(PR_SET_PDEATHSIG, SIGTERM);

      //close unused pipe ends
      close(outpipefd[1]);
      close(inpipefd[0]);

      //replace tee with your process
      execl("/usr/bin/gdb", "gdb", "test", "--interpreter=mi4", "--silent", (char*) NULL);

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