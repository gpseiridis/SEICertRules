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
            std::memset(buff.get(), 0, BufferSize);  // self note: you could delete this and still won't work
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
    if (inputNumber > 0)
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

    if (inputNumber > 0)
    {
        buff.reset(new char[BUFFER_SIZE]);
        //... do stuff
        someStr = std::strncpy(buff.get(), inputStr, BUFFER_SIZE - 1);
    }
    std::cout << "*Compliant2 * What will someStr print? someStr =  " << someStr << std::endl;
}

}  // namespace MEM50CPP

/*MEM51-CPP. Properly deallocate dynamically allocated resources */
namespace MEM51CPP
{
/*
Comments: Even better don’t use ‘new’ and ‘delete’ at all.
Adhere to cpp core guidelines, avoiding explicitly calling new+delete or calling malloc, free.
Try to use smart pointers or STL containers.
Sources from c++ core guidelines:
http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-newdelete
http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-mallocfree
 */

void nonCompliantExample1()
{
    int* array = new int[10];
    // ... do stuff
    delete array;
}

void compliantExample1()
{
    int* array = new int[10];
    // ... do stuff
    delete[] array;
}

void nonCompliantExample2()
{
    int* i = static_cast<int*>(std::malloc(sizeof(int)));
    // ... do stuff
    delete i;
}

void compliantExample2()
{
    int* i = static_cast<int*>(std::malloc(sizeof(int)));
    // ... do stuff
    std::free(i);
    std::cout << " ***** \n";
}

struct MyStruct
{
    ~MyStruct();
};

void nonCompliantExample3()
{
    MyStruct* s = new MyStruct();
    // ...
    std::free(s);
    std::cout << "called 'free' instead of 'delete' after dynamically allocating with 'new'";
}

void nonCompliantExample4()
{
    std::cout << "a std::unique_ptr is declared to hold a pointer to an object, \n";
    std::cout << "but is direct-initialized with an array of objects. \n";
    std::cout << "When the std::unique_ptr is destroyed, its default deleter calls delete instead of delete[]. \n";
    std::cout << "resulting in undefined behaviour. \n";

    std::unique_ptr<MyStruct> mySmartPtr{new MyStruct[10]};

    std::cout << " *********** Non Compliant Example with Shared Pointer ***********\n";
    /*
     In this noncompliant code example, a std::shared_ptr is declared to hold a pointer to an object, but is
     direct-initialized with an array of objects. As with std::unique_ptr, when the std::shared_ptr is destroyed, its
     default deleter calls delete instead of delete[], resulting in undefined behavior.
    */
    std::shared_ptr<MyStruct> mySharedPtr{new MyStruct[10]};
}

void compliantExample4()
{
    //  instead of a pointer to
    // an object. Additionally, std::make_unique() is used to initialize the smart pointer.

    std::cout << "In this compliant solution, the std::unique_ptr is declared to hold an array of objects. \n";
    std::cout << "instead of a pointer to an object \n";
    std::cout << "Additionally, std::make_unique() is used to initialize the smart pointer. (C++14) \n";

    //     std::unique_ptr<MyStruct[]> mySmartPtr = std::make_unique<MyStruct[]>(10); //C++ 14

    std::cout << " *********** Compliant Example with Shared Pointer ***********\n";
    /* Unlike the compliant solution for std::unique_ptr,
     * where std::make_unique() is called to create a unique pointer
     * to an array, it is ill-formed to call std::make_shared() with an array type.
     * Instead, this compliant solution
     * manually specifies a custom deleter for the shared pointer type,
     * ensuring that the underlying array is properly deleted. */
    std::shared_ptr<MyStruct> mySharedPtr{new MyStruct[10], [](const MyStruct* ptr) { delete[] ptr; }};
}

}  // namespace MEM51CPP