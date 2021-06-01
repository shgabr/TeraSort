#ifndef PARTITION_CPP_
#define PARTITION_CPP_

#include "Partition.h"
#include "QuickSort.cpp"

template <class T, typename S>
bool Partition<T,S>::resize ()
{
    if ( current == partition_size)
    {               //if number of elements in partition equal to partition_size then we need to assign more memory
        partition_size += increment;   //add increment value to partition_size
        data = (S *) realloc (data,partition_size*sizeof(S));    //allocate more memory to data
        dataWrapper = (T **) realloc (dataWrapper,partition_size*sizeof(T *));  //allocate more memory to dataWrapper
        memset (((char*) data)+(current*sizeof(S)),0,increment*sizeof(S));   //set added free memory spaces to zero
        memset (((char*) dataWrapper)+(current*sizeof(T*)),0,increment*sizeof(T*));  //set added free memory spaces to zero
        return true;
    }
    return false;
}
template <class T, typename S>
Partition<T,S>::Partition (FILE * f,uint64_t p_partition_size,uint64_t p_increment)
{
    partition_size = p_partition_size;   //set partition_size
    increment = p_increment;   //set the increment value
    current = 0;   //current is set to zero because it is empty
    output = f;   //set the ouput file
    data = (S *) calloc (partition_size,sizeof(S));  //allocate memory to data
    dataWrapper = (T **) calloc (partition_size,sizeof(T *));  //allocate memory to dataWrapper
}
template <class T, typename S>
void Partition<T,S>::addItem(S * s)
{
  mtx.lock();   //lock to ensure one thread can enter at a time
  resize();   //resize if needed
  memcpy (&data[current],s,sizeof(teraitem_r));  //copy item to data array
  current ++;   //increment current value
  mtx.unlock();  //unlock
}
template <class T, typename S>
void Partition<T,S>::sort()
{

    for ( uint64_t i = 0  ; i < partition_size ; i ++)
        dataWrapper[i] = new T (&data[i]);   //for every dataWrapper create a new object of teraSortItem
    QuickSort <T> quickSort (dataWrapper);   //sort the partition
    quickSort.quickSort(0,current-1);        //use quickSort to sort
}
template <class T, typename S>
void Partition<T,S>::dump()
{
    fwrite(data,sizeof(S),current,output);    //write the data to the file
}
template <class T, typename S>
Partition<T,S>::~Partition ()
{
    if ( data != NULL ) free(data);
    for ( uint64_t i = 0  ; i < partition_size ; i ++) delete (dataWrapper[i]);   //deletes every pointer to teraSortItem object created
    free(dataWrapper);   //free memory from dataWrapper
}
#endif
