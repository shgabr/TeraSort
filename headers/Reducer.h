#ifndef REDUCER_H
#define REDUCER_H

#include "defines.h"
#include "includes.h"
#include "Partitioner.cpp"

template <class T,typename S>
class Reducer
{
    private:
        Partition<T,S> * partition;   //pointer to partition
        std::thread * th;   //pointer to thread
    public:
        Reducer (Partition<T,S> * p_partition);   //parametrized constructor
        void execute ();   //sort every partition
        static void start(Reducer<T,S> * me);  //static function called by a thread
        void setThread(std::thread * p_th);  //setter for threads
        void waitForRunToFinish();   //wait for all threads to finish
        ~Reducer ();   //destructor

};
#endif
