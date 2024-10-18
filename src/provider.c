#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/prctl.h>


int main(int argc, char** argv)
{
  pid_t pid = 0;
  int inpipefd[2];
  int outpipefd[2];
  char buf[512];
  char msg[256];
  int status;

  pipe(inpipefd);
  pipe(outpipefd);
  pid = fork();
  if (pid == 0)
  {
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
    execl("/usr/bin/gdb", "gdb", "test", "--interpreter=mi3", "--silent", (char*) NULL);

    printf("Error\n");
    // Nothing below this line should be executed by child process. If so, 
    // it means that the execl function wasn't successfull, so lets exit:
    exit(1);
  }
  // The code below will be executed only by parent. You can write and read
  // from the child using pipefd descriptors, and you can send signals to 
  // the process using its pid by kill() function. If the child process will
  // exit unexpectedly, the parent process will obtain SIGCHLD signal that
  // can be handled (e.g. you can respawn the child process).

  //close unused pipe ends
  close(outpipefd[0]);
  close(inpipefd[1]);

  size_t n;

  // Now, you can write to outpipefd[1] and read from inpipefd[0] :  
  while(1)
  {

    /*printf("Enter message to send\n");
    scanf("%s", msg);
    if(strcmp(msg, "exit") == 0) break;*/
    
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