//#include <iostream>
//#include <memory>
//#include <cstring>
//
///*MEM50-CPP. Do not access freed memory */
//namespace MEM50CPP
//{
///*Omitted example is when trying to use ptr after delete */
///*Remember when the pointer is not pointing then we might have serious issues
// *Perhaps explain what does "free()" and "delete" actually do? Before you explain a buffer overflow*/
//void nonCompliantExample1(int inputNumber, const char* inputStr)
//{
//    const char* someStr = "";
//    if (inputNumber > 1)
//    {
//        enum
//        {
//            BufferSize = 32
//        };
//        try
//        {
//            /* The dynamically allocated memory managed by the buff object
//             * is accessed after it has been implicitly deallocated
//             * by the object's destructor.*/
//            std::unique_ptr<char[]> buff(new char[BufferSize]);
//            std::memset(buff.get(), 0, BufferSize);  // self note: you could delete this and still won't work
//            // ... do stuff
//            someStr = std::strncpy(buff.get(), inputStr, BufferSize - 1);
//        }
//        catch (std::bad_alloc&)
//        {
//            // Handle error
//        }
//    }
//    std::cout << "*Non Compliant* What will someStr print? someStr =  " << someStr << std::endl;
//}
//
//int compliantExample1(int inputNumber, const char* inputStr)
//{
//    std::unique_ptr<char[]> buff;
//    const char* someStr = "";
//
//    if (inputNumber > 1)
//    {
//        enum
//        {
//            BufferSize = 32
//        };
//        try
//        {
//            // In this compliant solution, the lifetime of the buff object extends past the point at which
//            // the memory managed by the object is accessed.
//
//            buff.reset(new char[BufferSize]);
//            std::memset(buff.get(), 0, BufferSize);
//
//            // ... do stuff
//            someStr = std::strncpy(buff.get(), inputStr, BufferSize - 1);
//        }
//        catch (std::bad_alloc&)
//        {
//            // Handle error
//        }
//    }
//
//    std::cout << "*Compliant* What will someStr print? someStr =  " << someStr << std::endl;
//}
//
//void nonCompliantExample2(int inputNumber, const char* inputStr)
//{
//    constexpr unsigned int BUFFER_SIZE = 32;
//    const char* someStr = "";
//    if (inputNumber > 0)
//    {
//        std::unique_ptr<char[]> buff(new char[BUFFER_SIZE]);
//        //... do stuff
//        someStr = std::strncpy(buff.get(), inputStr, BUFFER_SIZE - 1);
//    }
//    std::cout << "*Non Compliant2 * What will someStr print? someStr =  " << someStr << std::endl;
//}
//
//void compliantExample2(int inputNumber, const char* inputStr)
//{
//    constexpr unsigned int BUFFER_SIZE = 32;
//    const char* someStr = "";
//    std::unique_ptr<char[]> buff(new char[BUFFER_SIZE]);
//
//    if (inputNumber > 0)
//    {
//        buff.reset(new char[BUFFER_SIZE]);
//        //... do stuff
//        someStr = std::strncpy(buff.get(), inputStr, BUFFER_SIZE - 1);
//    }
//    std::cout << "*Compliant2 * What will someStr print? someStr =  " << someStr << std::endl;
//}
//
//}  // namespace MEM50CPP
//
///*MEM51-CPP. Properly deallocate dynamically allocated resources */
//namespace MEM51CPP
//{
///*
//Comments: Even better don’t use ‘new’ and ‘delete’ at all.
//Adhere to cpp core guidelines, avoiding explicitly calling new+delete or calling malloc, free.
//Try to use smart pointers or STL containers.
//Sources from c++ core guidelines:
//http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-newdelete
//http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-mallocfree
// */
//
//void nonCompliantExample1()
//{
//    int* array = new int[10];
//    // ... do stuff
//    delete array;
//}
//
//void compliantExample1()
//{
//    int* array = new int[10];
//    // ... do stuff
//    delete[] array;
//}
//
//void nonCompliantExample2()
//{
//    int* i = static_cast<int*>(std::malloc(sizeof(int)));
//    // ... do stuff
//    delete i;
//}
//
//void compliantExample2()
//{
//    int* i = static_cast<int*>(std::malloc(sizeof(int)));
//    // ... do stuff
//    std::free(i);
//    std::cout << " ***** \n";
//}
//
//struct MyStruct
//{
//    ~MyStruct();
//};
//
//void nonCompliantExample3()
//{
//    MyStruct* s = new MyStruct();
//    // ...
//    std::free(s);
//    std::cout << "called 'free' instead of 'delete' after dynamically allocating with 'new'";
//}
//
//void nonCompliantExample4()
//{
//    std::cout << "a std::unique_ptr is declared to hold a pointer to an object, \n";
//    std::cout << "but is direct-initialized with an array of objects. \n";
//    std::cout << "When the std::unique_ptr is destroyed, its default deleter calls delete instead of delete[]. \n";
//    std::cout << "resulting in undefined behaviour. \n";
//
//    std::unique_ptr<MyStruct> mySmartPtr{new MyStruct[10]};
//
//    std::cout << " *********** Non Compliant Example with Shared Pointer ***********\n";
//    /*
//     In this noncompliant code example, a std::shared_ptr is declared to hold a pointer to an object, but is
//     direct-initialized with an array of objects. As with std::unique_ptr, when the std::shared_ptr is destroyed, its
//     default deleter calls delete instead of delete[], resulting in undefined behavior.
//    */
//    std::shared_ptr<MyStruct> mySharedPtr{new MyStruct[10]};
//}
//
//void compliantExample4()
//{
//    //  instead of a pointer to
//    // an object. Additionally, std::make_unique() is used to initialize the smart pointer.
//
//    std::cout << "In this compliant solution, the std::unique_ptr is declared to hold an array of objects. \n";
//    std::cout << "instead of a pointer to an object \n";
//    std::cout << "Additionally, std::make_unique() is used to initialize the smart pointer. (C++14) \n";
//
//    //     std::unique_ptr<MyStruct[]> mySmartPtr = std::make_unique<MyStruct[]>(10); //C++ 14
//
//    std::cout << " *********** Compliant Example with Shared Pointer ***********\n";
//    /* Unlike the compliant solution for std::unique_ptr,
//     * where std::make_unique() is called to create a unique pointer
//     * to an array, it is ill-formed to call std::make_shared() with an array type.
//     * Instead, this compliant solution
//     * manually specifies a custom deleter for the shared pointer type,
//     * ensuring that the underlying array is properly deleted. */
//    std::shared_ptr<MyStruct> mySharedPtr{new MyStruct[10], [](const MyStruct* ptr) { delete[] ptr; }};
//}
//
//}  // namespace MEM51CPP
//
///*MEM52-CPP. Detect and handle memory allocation errors */
//namespace MEM52CPP
//{
//// T *p1 = new T; // Throws std::bad_alloc if allocation fails
//// T *p2 = new (std::nothrow) T; // Returns nullptr if allocation fails
////
//// T *p3 = new T[1]; // Throws std::bad_alloc if the allocation fails
//// T *p4 = new (std::nothrow) T[1]; // Returns nullptr if the allocation fails
//
//void nonCompliantExample1(const int* array, std::size_t size) noexcept
//{
//    /*In this noncompliant code example,
//     * an array of int is created using ::operator new[](std::size_t)
//     * and the results of the allocation are not checked.
//     * The function is marked as noexcept,
//     * so the caller assumes this function does not throw any exceptions.
//     * Because ::operator new[](std::size_t) can throw an exception if the allocation fails,
//     * it could lead to abnormal termination of the program. */
//    int* copy = new int[size];
//    std::memcpy(copy, array, size * sizeof(*copy));
//    // ...
//    delete[] copy;
//}
//
//void compliantExample1(const int* array, std::size_t size) noexcept
//{
//    /* Compliant Solution (std::nothrow)
//     * When using std::nothrow,
//     * the new operator returns either a null pointer or a pointer to the allocated space.
//     * Always test the returned pointer to ensure it is not nullptr before referencing the pointer.
//     * This compliant solution handles the error condition appropriately when the returned pointer is nullptr. */
//    int* copy = new (std::nothrow) int[size];
//    if (not copy)
//    {
//        // Handle error
//        return;
//    }
//    std::memcpy(copy, array, size * sizeof(*copy));
//    // ...
//    delete[] copy;
//}
//
//void compliantExample2(const int* array, std::size_t size) noexcept
//{
//    /* Compliant Solution (std::bad_alloc)
//     * Alternatively, you can use ::operator new[] without std::nothrow
//     * and instead catch a std::bad_alloc exception if sufficient memory cannot be allocated. */
//    int* copy;
//    try
//    {
//        copy = new int[size];
//    }
//    catch (std::bad_alloc)
//    {
//        // Handle error
//        return;
//    }
//    // At this point, copy has been initialized to allocated memory
//    std::memcpy(copy, array, size * sizeof(*copy));
//    // ...
//    delete[] copy;
//}
//
//void compliantExample3(const int* array, std::size_t size) noexcept(false)
//{
//    /* Compliant Solution (noexcept(false))
//     * If the design of the function is such that the caller is expected to handle exceptional situations,
//     * it is permissible to mark the function explicitly as one that may throw, as in this compliant solution.
//     * Marking the function is not strictly required,
//     * as any function without a noexcept specifier is presumed to allow throwing. */
//
//    int* copy = new int[size];
//    // If the allocation fails, it will throw an exception which the caller
//    // will have to handle.
//    std::memcpy(copy, array, size * sizeof(*copy));
//    // ...
//    delete[] copy;
//}
//
//// Non compliant example 2
///* In this noncompliant code example,
// * two memory allocations are performed within the same expression.
// * Because the memory allocations are passed as arguments to a function call,
// * an exception thrown as a result of one of the calls to new could result in a memory leak. */
//struct A
//{ /* ... */
//};
//struct B
//{ /* ... */
//};
//
//void g(A*, B*);
//void nonCompliantExample2()
//{
//    //  If A allocated first then B throws exception
//    //  Wrapping the call to g() in a try/catch block is insufficient because
//    //  it would be impossible to free the memory allocated for A.
//    g(new A, new B);
//}
//
//void compliantExample4()
//{
//    /*use unique_ptr
//     * If A is allocated but B throws exception,
//     * it would still result in the destruction and deallocation of the A object
//     * when then std::unique_ptr<A> was destroyed*/
//
//    // g(std::make_unique<A>(), std::make_unique<B>());  C++14
//}
//
//void g(A&, B&);
//void compliantExample5()
//{
//    /* Alternatively use References
//     * When possible, the more resilient compliant solution is to remove the memory allocation entirely
//     * and pass the objects by reference instead */
//    A a;
//    B b;
//    g(a, b);
//}
//
//}  // namespace MEM52CPP
//
///*MEM56-CPP. Do not store an already-owned pointer value in an unrelated smart pointer */
//namespace MEM56CPP
//{
//void nonCompliantExample1()
//{
//    /* In this non-compliant code example,
//     * two unrelated smart pointers are constructed from the same underlying pointer value.
//     * When the local, automatic variable p2 is destroyed,
//     * it deletes the pointer value it manages.
//     * Then, when the local, automatic variable p1 is destroyed, it deletes the same pointer value,
//     * resulting in a double-free vulnerability. */
//
//    // summary: p2 is destroyed releases i*. p1 destroyed releases same *i which was already released!
//    int* i = new int;
//    std::shared_ptr<int> p1(i);
//    std::shared_ptr<int> p2(i);
//}
//
//void compliantExample1()
//{
//    /* In this compliant solution,
//     * the std::shared_ptr objects are related to one another through copy construction.
//     * When the local, automatic variable p2 is destroyed,
//     * the use count for the shared pointer value is decremented but still nonzero.
//     *
//     * Then, when the local, automatic variable p1 is destroyed,
//     * the use count for the shared pointer value is decremented to zero,
//     * and the managed pointer is destroyed.
//     * This compliant solution also calls std::make_shared() instead of allocating a raw pointer
//     * and storing its value in a local variable.
//
// */
//    std::shared_ptr<int> p1 = std::make_shared<int>();
//    std::shared_ptr<int> p2(p1);
//}
//
//}  // namespace MEM56CPP