#include <iostream>
#include <memory>
#include <cstring>

/*MEM50-CPP. Do not access freed memory */
namespace MEM50CPP
{
/*Omitted example is when trying to use ptr after delete */

void nonCompliantExample1(int inputNumber, const char* inputStr)
{
    const char* someStr = "";
    if (inputNumber > 1)
    {
        enum
        {
            BufferSize = 32
        };
        try
        {
            /* The dynamically allocated memory managed by the buff object
             * is accessed after it has been implicitly deallocated
             * by the object's destructor.*/
            std::unique_ptr<char[]> buff(new char[BufferSize]);
            std::memset(buff.get(), 0, BufferSize); //self note: you could delete this and still won't work
            // ... do stuff
            someStr = std::strncpy(buff.get(), inputStr, BufferSize - 1);
        }
        catch (std::bad_alloc&)
        {
            // Handle error
        }
    }
    std::cout << "*Non Compliant* What will someStr print? someStr =  " << someStr << std::endl;
}

int compliantExample1(int inputNumber, const char* inputStr)
{
    std::unique_ptr<char[]> buff;
    const char* someStr = "";

    if (inputNumber > 1)
    {
        enum
        {
            BufferSize = 32
        };
        try
        {
            // In this compliant solution, the lifetime of the buff object extends past the point at which
            // the memory managed by the object is accessed.

            buff.reset(new char[BufferSize]);
            std::memset(buff.get(), 0, BufferSize);

            // ... do stuff
            someStr = std::strncpy(buff.get(), inputStr, BufferSize - 1);
        }
        catch (std::bad_alloc&)
        {
            // Handle error
        }
    }

    std::cout << "*Compliant* What will someStr print? someStr =  " << someStr << std::endl;
}


void nonCompliantExample2(int inputNumber, const char* inputStr)
{
    constexpr unsigned int BUFFER_SIZE = 32;
    const char* someStr = "";
    if(inputNumber >0)
    {
        std::unique_ptr<char[]> buff(new char[BUFFER_SIZE]);
        //... do stuff
        someStr = std::strncpy(buff.get(), inputStr, BUFFER_SIZE - 1);
    }
    std::cout << "*Non Compliant2 * What will someStr print? someStr =  " << someStr << std::endl;

}

void compliantExample2(int inputNumber, const char* inputStr)
{
    constexpr unsigned int BUFFER_SIZE = 32;
    const char* someStr = "";
    std::unique_ptr<char[]> buff(new char[BUFFER_SIZE]);

    if(inputNumber >0)
    {
        buff.reset(new char[BUFFER_SIZE]);
        //... do stuff
        someStr = std::strncpy(buff.get(), inputStr, BUFFER_SIZE - 1);
    }
    std::cout << "*Compliant2 * What will someStr print? someStr =  " << someStr << std::endl;
}

}  // namespace MEM50CPP
