/**
 * Functions to connect to gdb and interact with the program.
 * 
 * Functions have a C like implementation due to the original C implementation of this program.
 * 
 */
#ifndef __PROVIDER_H__
#define __PROVIDER_H__

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

using namespace std;

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
gdb_proc* gdb_connect();


/**
 * Clear the gdb process structure
 * 
 * @param proc a pointer to the structure to clear
 */
void gdb_close(gdb_proc* proc);


/**
 * Send data to gdb
 * 
 * @param
 * `input` the string to send. 
 * The string MUST terminate with '\n'.
 * 
 * @return 1 if the string was send, -1 if an error occured
 */
int gdb_send(gdb_proc* proc, char const* input);


/**
 * Read gdb output
 * 
 * @param
 * `proc` a gdb process
 * `buffer` a pointer to the output buffer
 * 
 * @return 0 if there is nothing to read, otherwise the size of the string placed in the buffer
 */
string gdb_read(gdb_proc* proc);



#endif