#ifndef PARTITIONER_CPP_
#define PARTITIONER_CPP_

#include "Partitioner.h"

template <class T, typename S>
Partitioner<T,S>::Partitioner (FILE * f,uint16_t p_partitions_count,uint64_t p_partition_expected_size)
{
    partitions_count = p_partitions_count;
    partitions = (Partition<T,S> **) calloc (partitions_count,sizeof(Partition<T,S> *));
    for ( uint16_t i = 0 ; i < partitions_count ; i++)
        partitions[i] = new Partition <T,S> (f,p_partition_expected_size,1000);   //for every partition create a new object Partition
    cutpoints = (T **) calloc (partitions_count-1,sizeof(T *));   //allocate memory for cutpoints
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
        cutpoints[i] = new T();   //for every cutpoint create new object of teraSortItem
}
template <class T, typename S>
void Partitioner<T,S>::addCutpoint(uint16_t index,T * t)
{
   cutpoints[index]->addToKeyValue(t->key());   //add cutpoints of similar index
}

template <class T, typename S>
void Partitioner<T,S>::calcCutpointsAverage(uint16_t p_mappers_count)
{
  for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
    cutpoints[i]->keyValueAverage(p_mappers_count);   //finds the average for every cutpoint of similar index

}

template <class T, typename S>
void Partitioner<T,S>::addItem(T * t)
{
    bool partition_set = false;
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
    {
        if (cutpoints[i]->getKeyValue() > t->key())  //checks the key of item is less than which cutpoint
        {
            partition_set = true;
            partitions[i]->addItem(t->getTeraItem());   //add item to appropriate partition
            break;
        }
    }
    if ( !partition_set) partitions[partitions_count-1]->addItem(t->getTeraItem());  //if not less than any cutpoint then add item to final partition

}

template <class T, typename S>
uint16_t Partitioner<T,S>::getPartitionsCount()
{
    return partitions_count;   //getter for partitions_count
}

template <class T, typename S>
Partition<T,S> * Partitioner<T,S>::getPartition (uint16_t index)
{
    if ( index < partitions_count) return partitions[index];   //getter for partitions
    else return NULL;
}

template <class T, typename S>
Partitioner<T,S>::~Partitioner ()
{
    for ( uint16_t i = 0 ; i < partitions_count ; i++)
        delete(partitions[i]);  //deletes every pointer to partitions
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
        delete(cutpoints[i]);   //deletes every cutpoint
    free(partitions);
    free(cutpoints);
}
#endif
