#include "universal_converter_to_string.h"

#include <iostream>
#include <cassert>
#include <functional>

template <typename T>
void f(std::function<std::string(const T&)> ref) {

}

int main() {
    // f<int>(&dev_toolkit::universal_converter_to_string<int>); CE
    f<int>(&dev_toolkit::details::const_universal_converter_to_string<int>);

    return 0;
}