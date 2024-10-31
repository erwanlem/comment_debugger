#ifndef __COMMAND__H__
#define __COMMAND__H__

/**
 * command structure
 * describe user input
 */
struct command
{
    char** files;
    int clear;
};


/**
 * Create struct command from program input values
 * 
 * @param
 * `argc` program argc value
 * `args` program argv values
 * 
 * @return `struct command*` a pointer to command struct
 */
struct command* parse_input(int argc, const char* args[]);



/**
 * Free command structure
 * 
 * @param `c` command structure to free
 */
void free_command(struct command* c);



#endif