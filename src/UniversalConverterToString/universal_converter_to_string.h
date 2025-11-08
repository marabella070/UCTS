#ifndef UNIVERSAL_CONVERTER_TO_STRING
#define UNIVERSAL_CONVERTER_TO_STRING

#include "string_conversion_traits.h"

#include <optional>
#include <sstream>

namespace dev_toolkit {

//TODO: прописать описание для этого чуда
//TODO: еще нужно сделать перегрузку с std::function для предоставления своего варианта развития событий
//TODO: Видимо следует это реализовывать через выкидывание исключения, если тип не может быть конвертирован, что более логично
//TODO: И сделать кастомный тип для исключения
template <typename T>
std::optional<std::string> universal_converter_to_string(T&& value) {
    if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string>) { return value; }

    if constexpr (std::is_same_v<std::remove_reference_t<T>, char> || 
                  std::is_same_v<std::remove_reference_t<T>, unsigned char>) {
        return std::string(1, value);
    }
    if constexpr (std::is_same_v<std::remove_reference_t<T>, bool>) {
        return (value) ? "true" : "false";
    }

    if constexpr (string_conversion_traits::is_to_string_compatible_v<T>) {
        return std::to_string(value); 
    }
    if constexpr (std::is_constructible_v<std::string, T>) { 
        return std::string(std::forward<T>(value)); 
    }
    if constexpr (string_conversion_traits::has_ostream_operator_v<T>) {
        std::stringstream oss;
        oss << (std::forward<T>(value));
        return oss.str();
    } 
    return std::nullopt;
}

} // dev_toolkit namespace

#endif // UNIVERSAL_CONVERTER_TO_STRING

