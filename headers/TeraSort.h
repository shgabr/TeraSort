#ifndef TERASORT_H
#define TERASORT_H

#include "defines.h"
#include "includes.h"
#include "Mapper.cpp"
#include "Reducer.cpp"
#include "Partitioner.cpp"


template <class T, typename S>
class TeraSort
{
    private:
        FILE * input;     //input file
        FILE * output;    //output file
        uint64_t file_byte_size;    //file size in bytes
        uint64_t file_record_size;   //number of records in file
        char input_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];  //character array for input_file_name
        char output_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE]; //character array for output_file_name
        uint16_t mappers;   //number of mappers
        uint16_t reducers;   //number of reducers
        uint64_t sample_size;  //size of the sample
        Mapper <T,S> ** map_engines;    //double pointer (array of pointers) to Mapper class
        Reducer <T,S> ** reduce_engines;  //double pointer (array of pointers) to Reducer class
        Partitioner <T,S> * partitioner;   //pointer to Partitioner class
    public:
        TeraSort (char * p_input_file_name,char * p_output_file_name,uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size);
              //parametrized constructor that recieves input file name, output file name, # of mappers, # of reducers, sample size
        void execute();   //method execute
        ~TeraSort();    //destructor 
};
#endif
