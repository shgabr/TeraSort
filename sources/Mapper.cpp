#ifndef MAPPER_CPP
#define MAPPER_CPP

#include "Mapper.h"
#include "QuickSort.cpp"


template <class T, typename S>
void Mapper<T,S>::phase1()
{
    cout << "Phase1" << endl;

    dataWrapper = (T **) calloc (read_count,sizeof(T *));   //assign memory to dataWrapper
    sample = (T **) calloc (sample_size,sizeof(T *));   //assign memory to sample
    for ( uint64_t i = 0  ; i < read_count ; i ++)
        dataWrapper[i] = new T (&data[i]);    //for every dataWrapper create a new object of teraSortItem

    uint64_t x;
    uint64_t c=0;
    while (c<sample_size){
      x = random(read_count);    //generate random number
      if (dataWrapper[x]->getb1() == 0){   //to ensure that no same values are taken
        sample[c] = dataWrapper [x];   //put value to sample
        dataWrapper[x]->setb1(1);    //set b1 to 1 to make it unique
        c++;
      }
    }

    for (uint64_t c=0; c<sample_size; c++)
      if (sample[c]->getb1() == 1)
        sample[c]->setb1(0);   //return back to values of b1 to 0 as not to change the original values

    QuickSort <T> sort (sample);
    sort.quickSort(0,sample_size-1);   //sort the sample

    for (uint16_t c=0; c<reducers-1; c++){
      partitioner->addCutpoint(c, sample[(sample_size/reducers)*(c+1)]);   //add cutpoints for every map of equal index
    }
}

template <class T, typename S>
void Mapper<T,S>::phase2()
{
    printf ("Start Shuffling .....\n");
    for ( uint64_t i = 0 ; i  < read_count ; i ++)
        partitioner->addItem(dataWrapper[i]);   //add item to appropriate partition
    printf ("Finished Shuffling .....\n");
}

template <class T, typename S>
Mapper<T,S>::Mapper (FILE * f,
                uint16_t p_reducers, //number of reducers
                uint64_t p_start,  //start of each map
                uint64_t p_count,  //the size of each map
                uint64_t p_sample_size,   //size of sample
                Partitioner<T,S> * p_partitioner)  //pointer to partitioner
{
    input = f;    //set data member input
    read_count = p_count;  //set data member read_count
    read_start = p_start;   //set data member read_start
    sample_size = p_sample_size;  //set data member sample_size
    reducers = p_reducers;   //set data member reducers
    dataWrapper = NULL;   ////set data member partition to NULL
    data = (S *) calloc (read_count,sizeof(S));   //assign memory yo data
    fseek(input,read_start*sizeof(S),SEEK_SET);   //seek from (start) * (size of element) to ensure every thread reads from a different location
    uint64_t read_items = fread(data,sizeof(S),read_count,f);    //read from file and save to data
    partitioner = p_partitioner;   //set data member partition
    phase = PHASE1;   //phase is assigned 1 for phase1
}


template <class T, typename S>
void Mapper<T,S>::execute ()
{
    if ( phase == PHASE1)   //if phase is equal 1
    {
        phase1();    //call phase1
        phase = PHASE2;  //set phase to 2
    }
    else if(phase == PHASE2) phase2(); //if phase is equal 2 then call phase2
}

template <class T, typename S>
void Mapper<T,S>::start (Mapper<T,S> * me)
{
    me->execute();   //call execute
}

template <class T, typename S>
void Mapper<T,S>::setThread(std::thread * p_th)
{
    th = p_th;    //set thread to thread data member
}

template <class T, typename S>
void Mapper<T,S>::waitForRunToFinish()
{
    th->join();    //wait for thread to finish
}

template <class T, typename S>
Mapper<T,S>::~Mapper()
{
    if (dataWrapper != NULL)
    {
        for ( uint64_t i = 0  ; i < read_count ; i ++) delete (dataWrapper[i]);  // deletes every pointer to teraSortItem object created
        free(dataWrapper);   //free memory from dataWrapper
    }
    free(data);    //free memory from data
    delete(th);   //delete threads
}

#endif
