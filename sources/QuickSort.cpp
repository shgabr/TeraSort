#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_

#include "QuickSort.h"

template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;   //set teraSortItem
}
template <class T>
int64_t QuickSort<T>::partition( int64_t l, int64_t r) {


  T * temp = teraSortItem[r];    // store the last element in a temp object
  int64_t c = l-1;     // get the leftmost index of the list

  for (int64_t i=l; i<=r-1; i++)
    if (teraSortItem[i]->key() <= temp->key())   //if temp is greater or equal than teraSortItem
    {
      c++;   //increment c
      teraSortItem[c]->swap(teraSortItem[i]);   //swap teraSortItem of c with i
    }
    teraSortItem[c+1]->swap(teraSortItem[r]);   //swap the rightmost teraSortItem with teraSortItem of c+1
    return (c+1);   //pivot index

}

template <class T>
void QuickSort<T>::quickSort( int64_t l, int64_t r)
{

  if ( l < r) {    //stopping case: if l>r

    int64_t pivot = partition(l, r);    //pivot index

    quickSort(l,pivot-1);    //recursive call decrementing r
    quickSort(pivot+1,r);    //recursive call incrementing l
  }
}

template <class T>
void QuickSort<T>::insertionSort (T ** item, int64_t size) {

  if ( size <= 1 ) return;   //if empty return
  for ( int64_t i = 1 ; i < size ; i ++) {
    T * tmp = item[i];    //store item i in temp pointer object
    int j = i;
    for( ;j >0&&tmp<item[j-1];j--)   //find the suitable location with previous elements
      item[j] = item[j-1];
    item[j]= tmp;    //save temp to the found location
  }

}

template <class T>
QuickSort<T>::~QuickSort()
{

}

#endif
