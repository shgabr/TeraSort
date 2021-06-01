#ifndef TERASORTITEM_H
#define TERASORTITEM_H
#include "defines.h"
#include "includes.h"

typedef struct    //a struct that is
{
        uint8_t key[10];
        uint8_t b1[2];
        char rowid[32];
        uint8_t b2[4];
        uint8_t filler[48];
        uint8_t b3[4];
}teraitem_r;

class TeraSortItem {
  private:
    teraitem_r * teraitem;    //pointer to teraitem_r
    uint128_t key_value;    // key value used in cutpoints
  public:
    TeraSortItem();   //default constructor
    TeraSortItem (TeraSortItem & teraSortItem);   //copy constructor
    TeraSortItem (teraitem_r  * p_teraitem);  //parametrized constructor
    void operator = (TeraSortItem * teraSortItem);  //operator overloaing
    uint128_t key ();  //returns key in uint128_t type
    void swap (TeraSortItem * p_teraSortItem);    //swaps two keys

    bool operator > (TeraSortItem * p_teraSortItem);  //operator overloaing
    bool operator < (TeraSortItem * p_teraSortItem);  //operator overloaing
    bool operator >= (TeraSortItem * p_teraSortItem);  //operator overloaing
    bool operator <= (TeraSortItem * p_teraSortItem); //operator overloaing
    bool operator == (TeraSortItem * p_teraSortItem); //operator overloaing
    bool operator != (TeraSortItem * p_teraSortItem); //operator overloaing
    teraitem_r * getTeraItem ();   //getter for teraitem
    void setb1 (uint8_t value);   //added: setter for b1
    uint8_t getb1 ();    //added: getter for b1
    void addToKeyValue(uint128_t p_key_value);   // add value to key_value
    uint128_t getKeyValue();  //getter for key_value
    void keyValueAverage(uint16_t p_divisor);  //calculate average of cutpoints
    uint16_t hash(uint16_t p_reducers);   //hashes data
    ~TeraSortItem();  //destructor
};


#endif
