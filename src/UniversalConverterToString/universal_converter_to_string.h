#ifndef UNIVERSAL_CONVERTER_TO_STRING
#define UNIVERSAL_CONVERTER_TO_STRING

#include "string_conversion_traits.h"

#include <sstream>
#include <exception>

namespace dev_toolkit {

class InvalidTypeConversionException : public std::exception {
public:
    const char* what() const noexcept override;
};

//TODO: прописать описание для этого чуда
//TODO: еще нужно сделать перегрузку с std::function для предоставления своего варианта развития событий
template <typename T>
std::string universal_converter_to_string(T&& value) {
    if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string>) { return value; }

    if constexpr (std::is_same_v<std::remove_reference_t<T>, char> || 
                  std::is_same_v<std::remove_reference_t<T>, unsigned char>) {
        return std::string(1, value);
    }
    if constexpr (std::is_same_v<std::remove_reference_t<T>, bool>) {
        return (value) ? "true" : "false";
    }

    if constexpr (string_conversion_traits::is_to_string_compatible_v<T>) {
        return std::to_string(std::forward<T>(value)); 
    }
    if constexpr (std::is_constructible_v<std::string, T>) { 
        return std::string(std::forward<T>(value)); 
    }
    if constexpr (string_conversion_traits::has_ostream_operator_v<T>) {
        std::stringstream oss;
        oss << (std::forward<T>(value));
        return oss.str();
    } 

    throw InvalidTypeConversionException();  // The type is not supported for conversion
    return "";
}

namespace details {
    
//TODO: тоже прописать зачем нужен этот КОСТЫЛЬ
template <typename T>
std::string const_universal_converter_to_string(const T& value) {
    return universal_converter_to_string(value);
}

} // details namespace

} // dev_toolkit namespace

#endif // UNIVERSAL_CONVERTER_TO_STRING

