#include "addons.h"

uint64_t random (uint64_t size){


  std::random_device dev;    //generates random number better pseudo-random
  std::mt19937 rng(dev());   //called Mersenne Twister Engine that generates a random number based on Mersenne Twister Algorithm
  std::uniform_int_distribution<std::mt19937::result_type> rnd (0,size);
            //produces random number integer values that are uniformily distributed over a closed interval (range)

  return rnd(rng);  //return the random number

  //the whole purpose of using this method to create a random number is to come as close as possible to a truly random number

}
