#pragma once
#include <iostream>
#include <cstdarg>
#include <type_traits>

/*Rule DCL50-CPP. Do not define a C-style variadic function*/
namespace DCL50CPP
{
int nonCompliantAddition(int first, int second, ...)
{
    std::cout << "The function reads arguments until the value 0 is found \n";
    std::cout << "Calling this function without passing the value 0 as an argument (after the first two arguments) "
                 "results in undefined behavior\n";
    std::cout << "Furthermore, passing any type other than an int also results in undefined behavior \n";

    int result = first + second;
    va_list va;
    va_start(va, second);
    while (int v = va_arg(va, int))
    {
        result += v;
    }
    va_end(va);
    std::cout << "what is my result = " << result << "\n";
    return result;
}

template <typename Arg, typename... Ts, typename std::enable_if<std::is_integral<Arg>::value>::type* = nullptr>
int compliantAddition(Arg i, Arg j, Ts... all)
{
    std::cout << "Expand the function parameter pack into a list of values as part of a braced initializer list \n";
    std::cout << "Since narrowing conversions are not allowed in a braced initializer list\n";
    std::cout
        << "the type safety is preserved despite the std::enable_if not involving any of the variadic arguments.\n";
    int values[] = {j, all...};
    int result = i;
    for (auto v : values)
    {
        result += v;
    }
    std::cout<<"result = " << result << "\n";
    return result;
}

}  // namespace DCL50CPP