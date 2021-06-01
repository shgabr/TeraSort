#ifndef PARTITIONER_H
#define PARTITIONER_H

#include "defines.h"
#include "includes.h"
#include "Partition.cpp"

template <class T, typename S>
class Partitioner
{
    private:
        Partition <T,S> ** partitions;  //array of pointers to partition
        uint16_t partitions_count;  //number of partitions
        T ** cutpoints;   //array of pointers to teraSortItem (represents cutpoints)
    public:
        Partitioner (FILE * f,uint16_t p_partitions_count,uint64_t p_partition_expected_size);  //parametrized constructor
        void addCutpoint(uint16_t index,T * t);   //add cutpoints of similar index of different maps
        void calcCutpointsAverage(uint16_t p_mappers_count);  //calculate average for every cutpoint of similar index
        void addItem(T * t);  //compares item to cutpoints to decide which partition to go in
        uint16_t getPartitionsCount();   //getter for partitions_count
        Partition <T,S> * getPartition (uint16_t index);  //getter for partitions
        ~Partitioner ();   //destructor
};

#endif
