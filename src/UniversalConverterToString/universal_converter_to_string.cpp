#include "universal_converter_to_string.h"

namespace dev_toolkit::ucts {

const char* InvalidTypeConversionException::what() const noexcept {
    return "It is impossible to convert the passed type to std::string!";
}

}  // namespace dev_toolkit::ucts
