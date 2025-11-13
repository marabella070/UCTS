#include <functional>  // for function
#include <iostream>    // for basic_ostream, cout, oper...
#include <string>      // for char_traits, basic_string

#include "universal_converter_to_string.h"  // for universal_converter_to_st...

class WithConvertOperator {
public:
    operator std::string() const { return "convert operator"; }
};

template <typename T>
void f(std::function<std::string(const T&)> ref) {}

int main() {
    // f<int>(&dev_toolkit::universal_converter_to_string<int>); CE
    f<int>(&dev_toolkit::ucts::const_universal_converter_to_string<int>);

    const int example_1 = 42;
    std::cout << dev_toolkit::ucts::universal_converter_to_string(example_1) << "\n";

    WithConvertOperator example_2;
    std::cout << dev_toolkit::ucts::universal_converter_to_string(example_2) << std::endl;

    return 0;
}