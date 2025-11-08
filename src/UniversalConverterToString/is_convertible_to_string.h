#ifndef IS_CONVERTIBLE_TO_STRING
#define IS_CONVERTIBLE_TO_STRING

#include "string_conversion_traits.h"

#include <type_traits>

namespace dev_toolkit {

template<class T>
struct is_convertible_to_string : std::integral_constant<bool,
    string_conversion_traits::is_to_string_compatible_v<T> ||
    std::is_constructible_v<std::string, T> ||
    string_conversion_traits::has_ostream_operator_v<T>
> {};

// Поведение при создании объекта std::string от объекта типа std::nullptr_t:
//
//  1. При c++23 и выше: возникает ошибка компиляции, так как конструктор от типа std::nullptr_t
//                       явно помечен как delete.
//
//  2. При c++20 и ниже: код успешно компилируется, но в runtime выбрасывается исключение:
//                          terminate called after throwing an instance of 'std::logic_error'
//                            what():  basic_string: construction from null is not valid
//                          Aborted (core dumped)
//
// Поэтому явно прописана заглушка на случай std::nullptr_t, чтобы is_convertible_to_string возвращала false:
template <>
struct is_convertible_to_string<std::nullptr_t> : std::false_type {};

template <typename T>
constexpr bool is_convertible_to_string_v = is_convertible_to_string<T>::value;

} // dev_toolkit namespace

#endif // IS_CONVERTIBLE_TO_STRING

