 #ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
//added 
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
       //k = tolower(k);
        
        unsigned long long conversion [6];
        int aNum [6];

        for (int n = 0; n < 5; ++n){
          conversion[n] = 0;
        }
        // first loop should increament by six
        int h = 0;
        for (int i = 0; i < k.size(); i+=6){
          //inititalize aNum to all zeros
          for (int j = 0; j < 6; ++i){
            aNum[j] = 0;
          }
          std::string sub;
          if (k.size() < 6){
            sub = k;
          }
          else{
            sub = k.substr(i, i+6);
          }
          int l = 0;
// inner loop should place values into aNum and loop condition j < subStr
          for (int k = sub.size()-1; k >= 0; --k){

              aNum[l] = letterDigitToNumber(sub[k]);
              ++l;
          }
// after breaking out of second loop letters should already be set and now do equation

          for (int m = 0; m < 6; ++m){
           conversion[h] += pow(36,5-m) * aNum[m];
          }
          ++h;
        }        
// do final hash equation and return.
        unsigned long long finalVal = 0;
        for (int p = 0; p < 5; ++p ){
          finalVal += rValues[p] * conversion[p];
        }
        return finalVal;

      // Add your code here
       
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if ( ( (letter - 97) >=0 ) && ( (letter - 97) < 26) ){
          return letter - 97;
        }
        else if (( (letter - 48) >=0 ) && ( (letter - 48) < 10)){
          return (letter - 48) + 26;

        }
        else if( ( (letter - 65) >=0 ) && ( (letter - 65) < 91)){
          return letter - 97;
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
