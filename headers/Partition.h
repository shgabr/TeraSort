#ifndef PARTITION_H
#define PARTITION_H

#include "defines.h"
#include "includes.h"

template <class T, typename S>
class Partition
{
    private:
        S * data;   //pointer to teraitem_r
        T ** dataWrapper;  //array of pointers to teraSortItem
        FILE * output;   //pointer to file output
        uint64_t partition_size;   //size of partition
        uint64_t current;    //the number of elements in partition
        uint64_t increment;   //the number of bytes to add when partition is full
        std::mutex mtx;    //mutex for locking and unlocking
        bool resize ();    //allocate more memory if partition is full
    public:
        Partition (FILE * f,uint64_t p_partition_size,uint64_t p_increment);  //parameterized constructor
        void addItem(S * s);   //add item to partition
        void sort();   //sorts the partition
        void dump();    //writes data to file
        ~Partition ();   //destructor
};

#endif
