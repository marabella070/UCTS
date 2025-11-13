#ifndef UNIVERSAL_CONVERTER_TO_STRING_H
#define UNIVERSAL_CONVERTER_TO_STRING_H

#include <exception>    // for exception
#include <sstream>      // for stringstream, nullptr_t
#include <string>       // for string, to_string
#include <type_traits>  // for remove_reference_t
#include <utility>      // for forward

#include "universal_converter_to_string_traits.h"

namespace dev_toolkit::ucts {

// A custom exception thrown by the universal_converter_to_string function,
// if the passed type cannot be converted to std::string.
class InvalidTypeConversionException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

/*
 * universal_converter_to_string — универсальный шаблон для преобразования значения любого(поддерживаемого) типа в
 * std::string. Поддерживает типы:
 *      1. перегруженные для функции std::to_string, то есть все арифметические,
 *      2. конструируемые в std::string - {const char*, StringViewLike, std::initilizer_list<char>},
 *      3. и с перегруженным оператором <<.
 * При попытке конвертации неподдерживаемого типа выбрасывает InvalidTypeConversionException.
 */
template <typename T>
std::string universal_converter_to_string(T&& value) {
    if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string>) {
        return value;
    }

    if constexpr (std::is_same_v<std::remove_reference_t<T>, char> ||
                  std::is_same_v<std::remove_reference_t<T>, unsigned char>) {
        return std::string(1, value);
    }
    if constexpr (std::is_same_v<std::remove_reference_t<T>, bool>) {
        return (value) ? "true" : "false";
    }

    if constexpr (traits::details::is_to_string_compatible_v<T>) {
        return std::to_string(std::forward<T>(value));
    }
    if constexpr (!std::is_same_v<std::remove_reference_t<T>, std::nullptr_t> &&
                  std::is_constructible_v<std::string, T>) {
        return std::string(std::forward<T>(value));
    }
    if constexpr (traits::details::has_ostream_operator_v<T>) {
        std::stringstream oss;
        oss << (std::forward<T>(value));
        return oss.str();
    }

    throw InvalidTypeConversionException();  // The type is not supported for conversion
    return "";
}

// Обертка над universal_converter_to_string с const T& сигнатурой
// Позволяет использовать конвертер там, где Явно требуется const ссылка
template <typename T>
std::string const_universal_converter_to_string(const T& value) {
    return universal_converter_to_string(value);
}

}  // namespace dev_toolkit::ucts

#endif  // UNIVERSAL_CONVERTER_TO_STRING_H
