#ifndef REDUCER_CPP_
#define REDUCER_CPP_

#include "Reducer.h"

template <class T, typename S>
Reducer<T,S>::Reducer (Partition<T,S> * p_partition)
{
    partition = p_partition;    //set partition
}
template <class T, typename S>
void  Reducer<T,S>::execute ()
{
    printf ("Launching Reducer Sort Engine...\n");
    partition->sort();   //sort every partition
    printf ("Reducer Sort Engine Terminated...\n");
}
template <class T, typename S>
void Reducer<T,S>::start (Reducer<T,S> * me)
{
    me->execute();    //call execute
}

template <class T, typename S>
void Reducer<T,S>::setThread(std::thread * p_th)
{
    th = p_th;    //set thread
}

template <class T, typename S>
void Reducer<T,S>::waitForRunToFinish()
{
    th->join();    //wait for threads to finish
}
template <class T, typename S>
Reducer<T,S>::~Reducer ()
{
    delete(th);    //deletes thread
}

#endif
