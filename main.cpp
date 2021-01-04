#include "CPPRules/Containers.h"
#include "CPPRules/Declerations.h"
#include "CPPRules/Strings.h"
#include "CPPRules/MemoryManagement.h"
#include "CRules/MemoryManagement.h"

#include <iostream>
#include <vector>

int main()
{
    /*********** C++ RULES  ***********/
    /*Rule 01. Declarations and Initialization (DCL) */
    DCL50CPP::nonCompliantAddition(13, 37, 1, 42, "hello", -4);
    DCL50CPP::compliantAddition(1, 2, 3, 0, 1);

    /*Rule 04. Containers (CTR) */
    std::vector<int> myVector = {1, 2, 3, 4, 5, 6, 7, 8};
    CTR52CPP::compliantExample3();
    CTR55CPP::compliantExample1(myVector);

    /*Rule 05. Characters and Strings (STR) */

    /*Rule 06. Memory Management (MEM) */
//    MEM50CPP::nonCompliantExample1(42, "hello");
//    MEM50CPP::nonCompliantExample2(20, "hello people");
//    MEM50CPP::compliantExample1(42, "hello");
//    MEM50CPP::compliantExample2(42, "hello people");
//
//    MEM51CPP::nonCompliantExample1();
//    MEM51CPP::nonCompliantExample2();
//    MEM51CPP::nonCompliantExample3();
//    MEM51CPP::nonCompliantExample4();
//    MEM51CPP::compliantExample1();
//    MEM51CPP::compliantExample2();

    /*********** C RULES  ***********/
    /*Rule 08. Memory Management (MEM) */


}
