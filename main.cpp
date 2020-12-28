#include <iostream>
#include "CPPRules/Containers.h"
#include <vector>


int main()
{

    /*Rule CTR52-CPP Guarantee that library functions do not overflow*/
    std::vector<int> myVector = {1,2,3,4,5,6,7,8};
//    CTR52CPP::nonCompliantxample1(myVector); //segfault
//    CTR52CPP::compliantExample1(myVector);
    CTR52CPP::compliantExample3();
    CTR55CPP::compliantExample1(myVector);

}
