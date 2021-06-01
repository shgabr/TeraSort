#ifndef TERASORT_CPP
#define TERASORT_CPP

#include "TeraSort.h"

template <class T, typename S>
TeraSort<T,S>::TeraSort (char * p_input_file_name,char * p_output_file_name,
                            uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size)
{
    input = fopen (p_input_file_name,"rb");      //opens input file with mode "read bytes"
    output = fopen (p_output_file_name,"wb");   //opens output file with mode "write bytes"
    file_byte_size = 0 ;           //set file_byte_size to zero
    file_record_size = 0 ;        //set file_record_size to zero
    mappers = p_mappers;          //set mappers to the parameter mapper
    reducers = p_reducers;         //set reducers to the parameter reducers
    sample_size = p_sample_size;     //set sample_size to the parameter sample_size
    map_engines = NULL;           //set Mapper pointer to NULL
    partitioner=NULL;           //set Partitioner pointer to NULL
    if ( input != NULL && output != NULL)    //if both files opened correctly
    {
       fseek (input,0,SEEK_END);     //seek to end of file
       file_byte_size = ftell(input);   //get current position in file and save to file_byte_size
       rewind (input);      //rewind pointer back to the beginning of the file
       file_record_size = file_byte_size/sizeof(S);    //file_record_size is the (file size) / (size of a single element)

       partitioner = new Partitioner <T,S> (output, reducers, 50);   //initialize new Partitioner

       map_engines = new Mapper <T,S> * [mappers];    //initialize new Mapper
       for ( uint16_t i = 0 ; i  < mappers; i++)    //loop for number of mappers
          map_engines[i] = new Mapper <T,S> (input, reducers, ((file_record_size)*i)/mappers, (file_record_size)/mappers, sample_size, partitioner);
              //for every mapper create a new object Mapper and give each mapper a different starting position in file
    } else {
      cout << "Error opening files" << endl;  //if file did not open correctly
      exit(1);   //terminate
    }
}

template <class T, typename S>
void TeraSort<T,S>::execute()
{
    printf ("Terasort Start Execute\n");
    for ( uint16_t i = 0 ; i  < mappers; i++)     //loop for number of mappers
    {
        std::thread * th = new std::thread(Mapper<T,S>::start, map_engines[i]);   //create a new thread for every mapper
        map_engines[i]->setThread(th);   //setThread for every mapper
    }

     for ( uint16_t i = 0 ; i  < mappers; i++)
         map_engines[i]->waitForRunToFinish();    //wait for every thread to finish

     partitioner->calcCutpointsAverage(mappers);    //calculate the average for every cutpoint

     for ( uint16_t i = 0 ; i  < mappers; i++)    //loop for number of mappers
     {
         std::thread * th = new std::thread(Mapper<T,S>::start, map_engines[i]);  //create a new thread for every mapper again
         map_engines[i]->setThread(th);   //setThread for every mapper again
     }

     for ( uint16_t i = 0 ; i  < mappers; i++)
         map_engines[i]->waitForRunToFinish();   //wait for all thread to finish

     reduce_engines = new Reducer <T,S> * [reducers];    //initialize new Reducer
     for ( uint16_t i = 0 ; i  < reducers; i++)    //loop over number of reducers
     {
       reduce_engines[i] = new Reducer <T,S> (partitioner->getPartition(i));  //create new object Reducer and give it a different partition
       std::thread * th = new std::thread(Reducer<T,S>::start, reduce_engines[i]);  //create a new thread for every Reducer
       reduce_engines[i]->setThread(th);   //set thread for every reducer
     }

     for ( uint16_t i = 0 ; i  < reducers; i++)
        reduce_engines[i]->waitForRunToFinish();   //wait for every reducer thread to finish


    for ( uint16_t i = 0 ; i  < reducers; i++)
        partitioner->getPartition(i)->dump();    //get every partition and dump it into file

}
template <class T, typename S>
TeraSort<T,S>::~TeraSort()
{
    if ( input != NULL) fclose (input);     //closes input file if open
    if ( output != NULL) fclose (output);    //closes output file if open
    if ( map_engines != NULL)
    {
        for ( uint16_t i = 0 ; i  < mappers; i++)
            delete (map_engines[i]);       // deletes every pointer to mapper object created
        free(map_engines);              //free the double pointer data member
    }
    if ( partitioner != NULL ) delete(partitioner);   //deletes partitioner

    if ( reduce_engines != NULL)
    {
        for ( uint16_t i = 0 ; i  < reducers; i++)
            delete (reduce_engines[i]);       // deletes every pointer to reducer object created
        free(reduce_engines);     //free the double pointer data member
    }

}

#endif
