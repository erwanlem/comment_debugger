/**
 * command structure
 * describe options privoded by user
 */
struct command
{
    char* file;
    bool clear;
};



command parse_input(char* input);