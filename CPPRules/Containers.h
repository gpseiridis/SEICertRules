#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

/*Rule CTR52-CPP Guarantee that library functions do not overflow*/
namespace CTR52CPP
{
void nonCompliantExample1(const std::vector<int>& src)
{
    std::cout << "the std::copy() algorithm provides no inherent bounds checking "
                 "and can lead to a buffer overflow. "
              << "\n";
    std::vector<int> dest;
    std::copy(src.begin(), src.end(), dest.begin());
}

void compliantExample1(const std::vector<int>& src)
{
    std::cout << "Sufficient Initial Capacity; "
                 "Initialize dest with src.size() default-inserted elements "
              << "\n";
    std::vector<int> dest(src.size());
    std::copy(src.begin(), src.end(), dest.begin());
    // do stuff
    std::cout << "**** end of compliantExample1 ****\n";
}
void compliantExample2(const std::vector<int>& src)
{
    std::cout
        << "Per Element Growth; "
           "An alternative approach is to supply a std::back_insert_iterator as the destination argument. This "
           "iterator expands the destination container by one element for each element supplied by the algorithm, "
           "which guarantees the destination container will become sufficiently large to hold the elements provided \n";

    std::vector<int> dest;
    std::copy(src.begin(), src.end(), std::back_inserter(dest));
    // do stuff
    std::cout << "**** end of compliantExample2 ****\n";
}

void nonCompliantExample2()
{
    std::vector<int> v;
    std::fill_n(v.begin(), 10, 0x42);

    for (const auto& elem : v)
    {
        std::cout << " elem --> " << elem << "\n";
    }
}

void compliantExample3()
{
    std::cout << "Give enough capacity1 \n";

    std::vector<int> myVector1(10);
    std::fill_n(myVector1.begin(), 10, 0x42);

    std::cout << "Alternatively, even simpler \n";
    std::vector<int> myVector2(10, 0x42);

    for (const auto& elem : myVector2)
    {
        std::cout << " elem --> " << elem << "\n";
    }
}
}  // namespace CTR52CPP
