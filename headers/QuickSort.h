#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "TeraSortItem.h"

template <class T>
class QuickSort{
    private:
        T ** teraSortItem;   //array of pointers to teraSortItem
        int64_t partition( int64_t l, int64_t r);  //partition to compare key and swap if needed
        void insertionSort (T ** item, int64_t list_size);  //another type of sorting algorithm
    public:
        QuickSort(T ** p_teraSortItem);   //parameterized constructor
        void quickSort( int64_t l, int64_t r);  //quicksort algorithm recursive in nature
        ~QuickSort();  //destructor
};

#endif
