#ifndef COMMANDLINEARGUMENTS_H
#define COMMANDLINEARGUMENTS_H

#include "TeraSort.cpp"
#include "TeraSortItem.h"



class CommandLineArguments
{
    private:
        char input_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];   //character array for input_file_name
        char output_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];  //character array for output_file_name
        uint16_t mappers;   //number of mappers
        uint16_t reducers;   //number of reducers
        uint64_t sample_size;  // size of the sample
        char error_string[ERROR_STRING_MAX_SIZE];   //character array for error string
    public:
        CommandLineArguments();   //default constructor
        bool parser(int argc,char ** argv);   //method to parse command line arguments
        bool execute();   // execute method
        char * getErrorString();   //getter of error_string
        ~CommandLineArguments();   //destructor
};

#endif
