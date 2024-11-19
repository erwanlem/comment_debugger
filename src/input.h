#ifndef __INPUT__H__
#define __INPUT__H__

#include <vector>
#include <string>

/**
 * Interpreter for user inputs.
 */
class Input {
    private:
    std::vector<std::string> files;
    std::vector<std::string> flags;
    int get_extension(const char* str);
    bool isFlag(const char* str);
    std::string getFlag(const char* str);


    public:
    Input() : files(), flags() {};



    /**
     * Interpret user input.
     * The parameters must come directly from the main.
     * @param argc size of argv
     * @param argv arguments
     */
    void interpret(int argc, char const *argv[]);



    /**
     * Return files extracted using `interpret` method
     * 
     * @return interpreted files
     * @warning It returns an empty vector if interpret has not been called
     */
    std::vector<std::string> getFiles();



    /**
     * Return flags extracted using `interpret` method
     * 
     * @return interpreted flags
     * @warning It returns an empty vector if interpret has not been called
     */
    std::vector<std::string> getFlags();
};


#endif