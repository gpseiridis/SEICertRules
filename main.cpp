#include "CPPRules/Containers.h"
#include "CPPRules/Declerations.h"
#include <iostream>
#include <vector>


int main()
{
    /*Rule 01. Declarations and Initialization (DCL) */
    DCL50CPP::nonCompliantAddition(13, 37, 1,42,"hello",-4);
    DCL50CPP::compliantAddition(1,2,3,0,1);

    /*Rule 04. Containers (CTR) */
    std::vector<int> myVector = {1,2,3,4,5,6,7,8};
    CTR52CPP::compliantExample3();
    CTR55CPP::compliantExample1(myVector);




}
