#ifndef __INPUT__H__
#define __INPUT__H__

#include <vector>
#include <string>

enum Language {
    C,
    CPP,
    OCAML,
    RUST,
    UNKNOWN
};


/**
 * Interpreter for user inputs.
 */
class Input {
    private:
    Language language;
    std::vector<std::string> files;
    std::vector<std::string> flags;
    std::string command;
    std::string output;

    int get_extension(const char* str);
    bool isFlag(const char* str);
    std::string getFlag(const char* str);


    public:
    Input() : language(UNKNOWN), files(), flags() {};



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
    std::vector<std::string> getFiles() const;



    /**
     * Return flags extracted using `interpret` method
     * 
     * @return interpreted flags
     * @warning It returns an empty vector if interpret has not been called
     */
    std::vector<std::string> getFlags() const;


    /**
     * Return the input detected language.
     * 
     * @return the detected language
     */
    Language getLanguage() const {return language;}


    /**
     * Build the command with all flags and files.
     * 
     * @example 
     * Example of output: -o name file.cpp
     * 
     * @return the command without the compiler call
     */
    std::string fullCommand() const {return command;};



    std::string getOutput() const {return output;};
};


#endif