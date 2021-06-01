#include "TeraSortItem.h"

static uint64_t POWERS[11] = {1,
                                    37,
                                    0x0559,
                                    0x0C5DD,
                                    0x1C98F1,
                                    0x04221AD5,
                                    0x98EDE0C9,
                                    0x0161A617D0D,
                                    0x0331D01712E1,
                                    0x076331355BA85,
                                    0x0111561CB63F539};


TeraSortItem::TeraSortItem()
{
    key_value=  0;      //default constructor
}
TeraSortItem::TeraSortItem (TeraSortItem & teraSortItem)
{
    memcpy(teraitem,teraSortItem.teraitem,sizeof(teraitem_r));
    key_value=  teraSortItem.key_value;;     //copy data from an object to another object
}
TeraSortItem::TeraSortItem (teraitem_r  * p_teraitem)
{
    teraitem = p_teraitem;
    key_value=  0;           //parametrized constructor
}
void TeraSortItem::operator = (TeraSortItem * teraSortItem)
{
    memcpy(teraitem,teraSortItem->teraitem,sizeof(teraitem_r));
    key_value=  teraSortItem->key_value;     //operator overloading to function the same as a copy constructor
}
uint128_t TeraSortItem::key()
{
    uint8_t * v = teraitem->key;
    uint128_t k =0;
    uint8_t * c = (uint8_t *) &k;
    c[0] = v[9];
    c[1] = v[8];
    c[2] = v[7];
    c[3] = v[6];
    c[4] = v[5];
    c[5] = v[4];
    c[6] = v[3];
    c[7] = v[2];
    c[8] = v[1];
    c[9] = v[0];
    return k;

    //converts the key to a uint128_t type and return it
}

void TeraSortItem::swap (TeraSortItem * p_teraSortItem)
{
  //swap two teraitems of two classes

    teraitem_r * s_teraitem = p_teraSortItem->teraitem;
    teraitem_r p_teraitem;
    memcpy(&p_teraitem,s_teraitem,sizeof(teraitem_r));
    memcpy(s_teraitem,teraitem,sizeof(teraitem_r));
    memcpy(teraitem,&p_teraitem,sizeof(teraitem_r));
}

bool TeraSortItem::operator > (TeraSortItem * p_teraSortItem)
{
    return ( key() > p_teraSortItem->key());   //operator overloaing comparing keys
}
bool TeraSortItem::operator < (TeraSortItem * p_teraSortItem)
{
    return ( key() < p_teraSortItem->key());  //operator overloaing comparing keys
}
bool TeraSortItem::operator >= (TeraSortItem * p_teraSortItem)
{
    return ( key() >= p_teraSortItem->key());   //operator overloaing comparing keys
}
bool TeraSortItem::operator <= (TeraSortItem * p_teraSortItem)
{
    return ( key() <= p_teraSortItem->key());  //operator overloaing comparing keys
}

bool TeraSortItem::operator == (TeraSortItem * p_teraSortItem)
{
    return ( key() == p_teraSortItem->key());  //operator overloaing comparing keys

}
bool TeraSortItem::operator != (TeraSortItem * p_teraSortItem)
{
    return ( key() != p_teraSortItem->key());  //operator overloaing comparing keys

}
uint16_t TeraSortItem::hash(uint16_t p_reducers)
{
    uint64_t h= 0 ;
    for ( uint8_t i =10 ; i > 0 ; i --)
        h+= teraitem->key[i-1] * POWERS[i-1];   //hashes data to mutiples of 10 to the powerof 37
    return h%p_reducers;
}

teraitem_r * TeraSortItem::getTeraItem ()
{
    return teraitem;    //getter for teraitem
}
void TeraSortItem::setb1 (uint8_t value)
{
  teraitem->b1[0] = value;   //setter for b1
}
uint8_t TeraSortItem::getb1 ()
{
    return teraitem->b1[0];  //getter for b1
}
void TeraSortItem::addToKeyValue(uint128_t p_key_value)
{
    key_value += p_key_value;    // add values to key_value
}
uint128_t TeraSortItem::getKeyValue()
{
    return key_value;     //getter for key_value
}
void TeraSortItem::keyValueAverage(uint16_t p_divisor)
{
    key_value /= p_divisor;   //calculate average of cutpoints
}


TeraSortItem::~TeraSortItem()
{

}
