#ifndef __PROVIDER_H__
#define __PROVIDER_H__

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Gdb process structure
 * 
 * This structure contains:
 *      - the pid of the gdb process
 *      - the input pipe to send data to the process
 *      - the output pipe to get output data of the process
 */
struct gdb_proc {
    pid_t pid;
    int* input_pipe;
    int* output_pipe;
};


/**
 * Create a process running gdb
 * 
 * @return the structure of the created process
 * or NULL if an error occured
 */
struct gdb_proc* gdb_connect();


/**
 * Clear the gdb process structure
 * 
 * @param proc a pointer to the structure to clear
 */
void gdb_close(struct gdb_proc* proc);


/**
 * Send data to gdb
 * 
 * @param
 * `input` the string to send. 
 * The string MUST terminate with '\n'.
 * 
 * @return 1 if the string was send, -1 if an error occured
 */
int gdb_send(char* input);


/**
 * Read gdb output
 * 
 * @param
 * `buffer` a pointer to the output buffer
 * 
 * @return 0 if there is nothing to read, otherwise the size of the string placed in the buffer
 */
int gdb_read(char* buffer);



#endif