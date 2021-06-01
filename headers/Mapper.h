#ifndef MAPPER_H
#define MAPPER_H

#include "defines.h"
#include "includes.h"
#include "Partitioner.cpp"

template <class T, typename S>
class Mapper
{
    private:
        S * data;    //data read from file
        T ** dataWrapper;   //array of pointers to teraSortItem
        T ** sample;   //array of pointers to teraSortItem (a random sample from dataWrapper)
        FILE * input;  //input file
        uint8_t phase;   //phase index
        uint16_t reducers;  //number of reducers
        uint64_t read_start;   //the starting index for each map to start from reading
        uint64_t read_count;   //the size of each map
        uint64_t sample_size;   //the size of the sample
        std::thread * th;    //threads
        Partitioner<T,S> * partitioner;   //pointer to partitioner
        void phase1();   //private method phase1  (create sample or sort it to get cutpoints)
        void phase2();   //private method phase2  (add item to appropriate partition)
    public:
        Mapper (FILE * f,
                uint16_t reducers, //number of reducers
                uint64_t p_start,  //start of each map
                uint64_t p_count,  //size of each map
                uint64_t p_sample_size,  //size of sample
                Partitioner<T,S> * p_partitioner);
        void execute ();   //execute that calls either phase1 or phase2
        static void start(Mapper<T,S> * me);  //static function called by a thread
        void setThread(std::thread * p_th);  //setter for threads
        void waitForRunToFinish();   //wait for all threads to finish
        ~Mapper ();   //destructor
};

#endif
