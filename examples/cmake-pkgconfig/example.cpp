#include <iostream>
#include <termcolor/termcolor.hpp>

int main()
{
    std::cout << termcolor::red << "Hello, World!" << termcolor::reset << std::endl;
    return 0;
}
