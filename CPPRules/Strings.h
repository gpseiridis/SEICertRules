#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

/*STR50-CPP. Guarantee that storage for strings has sufficient space for character data
 * and the null terminator*/
namespace STR50CPP
{
void nonCompliantExample()
{
    // Just don't...
    char bufOne[12];
    char bufTwo[12];
    std::cin.width(12);
    std::cin >> bufOne;
    std::cin >> bufTwo;
}

void compliantExample()
{
    // simply use std::string
    std::string input;
    std::string stringOne, stringTwo;
    std::cin >> stringOne >> stringTwo;
}
}  // namespace STR50CPP

/* STR51-CPP. Do not attempt to create a std::string from a null pointer */
namespace STR51CPP
{
void nonCompliantExample()
{
    // In this noncompliant code example, a std::string object is created from the results of a call to std::getenv().
    // However, because std::getenv() returns a null pointer on failure, this code can lead to undefined behavior when
    // the environment variable does not exist (or some other error occurs).
    std::string tmp(std::getenv("TMP"));
    if (!tmp.empty())
    {
        // ...
    }
}

void compliantExample()
{
    // In this compliant solution, the results from the call to std::getenv() are checked for null before the
    // std::string object is constructed.
    const char* tmpPtrVal = std::getenv("TMP");
    std::string tmp(tmpPtrVal ? tmpPtrVal : "");
    if (not tmp.empty())
    {
        // do stuff
    }
}

}  // namespace STR51CPP