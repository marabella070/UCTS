#ifndef UNIVERSAL_CONVERTER_TO_STRING_TRAITS_H
#define UNIVERSAL_CONVERTER_TO_STRING_TRAITS_H

#include <ostream>
#include <type_traits>

namespace dev_toolkit::ucts::traits {

namespace details {

// ----------------------------------------------- has_ostream_operator -----------------------------------------------

/*
 * has_ostream_operator<T> - позволяет проверить определен ли оператор вывода в поток со следующей сигнатурой:
 *      [any_return_type] operator<<(std::ostream&, [type_that_can_take_T]);
 *
 *  1. any_return_type - так как это trait создается специально под UCTS, то явная специализация возвращаемого
 *      значения не требуется, потому что работа с потоком будет вестись на уровне std::stringstream и только для
 *      получения конечной строки.
 *
 *      1.1. Eсли [any_return_type != ostream&], то следующий код вызовет ошибку компиляции:
 *          ostream.operator<<(T) [<< std::endl;] - возможно CE
 *
 *  2. type_that_can_take_T - сигнатура принимаего значения в операторе, регулируется шаблонным параметром T, так
 *      например для получения стандартной сигнатуры оператора вывода в поток, переданный тип должен быть
 *      следующим - [const T&].
 */
template <typename T, typename = void>
struct has_ostream_operator : std::false_type {};

template <typename T>
struct has_ostream_operator<T, std::void_t<decltype(operator<<(std::declval<std::ostream&>(), std::declval<T>()))>>
    : std::true_type {};

template <typename T>
constexpr bool has_ostream_operator_v = has_ostream_operator<T>::value;

// ---------------------------------------- has_to_string_conversion_operator ----------------------------------------

/*
 * has_to_string_conversion_operator - позволяет проверить определен ли оператор приведения типа к std::string.
 *
 *  1. Результат зависит от типа, передаваемого шаблоного параметра T, а точнее от вида его value, то есть:
 *
 *      1.1 rvalue-ref[T/T&&] - будет искать перегрузку оператора от rvalue:
 *          [operator std::string() <const & || &&>],
 *
 *      1.2 lvalue-ref[T&] - будет искать перегрузку оператора от lvalue:
 *          [operator std::string() <const & || &>].
 */
template <typename T, typename = void>
struct has_to_string_conversion_operator : std::false_type {};

template <typename T>
struct has_to_string_conversion_operator<T, std::void_t<decltype(std::declval<T>().operator std::string())>>
    : std::true_type {};

template <typename T>
constexpr bool has_to_string_conversion_operator_v = has_to_string_conversion_operator<T>::value;

// ---------------------------------------------- is_convertible_to_base ----------------------------------------------

/*
 * is_convertible_to_base - позволяет проверить унаследован ли переданный тип от класса std::string и возможно ли
 * приведение типа наследника к родителю. Так же есть причина почему для этой проверки "не совсем" подходит
 * std::is_base_of:
 *
 *  1. Почему не с помощью std::is_base_of, можно понять из его "возможной"(cppreference) реализации:
 *
 *       namespace details
 *       {
 *           [...]
 *
 *           template<typename B, typename D>
 *           auto test_is_base_of(int) -> decltype(test_ptr_conv<B>(static_cast<D*>(nullptr)));
 *
 *           template<typename, typename>
 *           auto test_is_base_of(...) -> std::true_type; // private or ambiguous base
 *       }
 *
 *       template<typename Base, typename Derived>
 *       struct is_base_of : std::integral_constant<bool, [...] && decltype(details::test_is_base_of<Base,
 * Derived>(0))::value> {};
 *
 *  В случае private/protected наследования классов, приведение типа наследника к родительскому запрещено стандартном -
 *  это следует учитывать для реализации желаемого функционала. Именно в этом моменте std::is_base_of не отвечает
 *  нашим требованиям, а именно:
 *
 *      (*) Пусть D private/protected наследник B, тогда при вызове is_base_of<B, D>, вызовется дополнительная функция
 *      test_is_base_of<B, D>, в спецификации шаблона произойдет неудачная подстановка указателя D* под B*(вот тут
 *      test_ptr_conv<B>(static_cast<D*>(nullptr))), и будет выбрана общая версия функции, что вернет тип
 *      std::true_type, что не верно, если мы хотим проверить типы на приведение друг к другу.
 *
 *  2. Пусть D наследник B, тогда при следующем вызове is_convertible_to_base<D, B> - вернет std::false_type, это
 *      говорит о том, что функция поддерживает только понижающий каст.
 */
template <typename B, typename D>
using is_convertible_to_base = std::is_convertible<D*, B*>;

template <typename B, typename D>
constexpr bool is_convertible_to_base_v = is_convertible_to_base<B, D>::value;

// --------------------------------------------- is_to_string_compatible ---------------------------------------------

/*
 * is_to_string_compatible - позволяет проверить перегружена ли стандартная функция std::to_string для переданного типа.
 *
 *  1. Результат зависит от типа, передаваемого шаблоного параметра T, а точнее от вида его value, то есть:
 *
 *      1.1 rvalue-ref[T/T&&] - будет искать перегрузку функции, которая принимает rvalue:
 *          [std::to_string(<const T& || T&&>)],
 *
 *      1.2 lvalue-ref[T&] - будет искать перегрузку функции, которая принимает lvalue:
 *          [std::to_string(<const T& || T&>)].
 */
template <typename T, typename = void>
struct is_to_string_compatible : std::false_type {};

template <typename T>
struct is_to_string_compatible<T, std::void_t<decltype(std::to_string(std::declval<T>()))>> : std::true_type {};

template <typename T>
constexpr bool is_to_string_compatible_v = is_to_string_compatible<T>::value;

}  // namespace details

/*
 * is_convertible_to_string — типовой трейд, проверяющий, может ли тип T быть преобразован в std::string.
 *  Вернет true, для следующих поддерживаемых типов:
 *      1. перегруженных для функции std::to_string, то есть всех арифметических,
 *      2. конструируемых в std::string - {const char*, StringViewLike, std::initilizer_list<char>},
 *      3. и перегруженных оператором <<.
 */
template <class T>
struct is_convertible_to_string
    : std::integral_constant<bool, details::is_to_string_compatible_v<T> || std::is_constructible_v<std::string, T> ||
                                       details::has_ostream_operator_v<T>> {};

/* Рассмотрение крайнего случая, при входящем типе std::nullptr_t:
 *
 * Поведение при создании объекта std::string от объекта типа std::nullptr_t:
 *
 *  1. При c++23 и выше: возникает ошибка компиляции, так как конструктор от типа std::nullptr_t
 *                       явно помечен как delete.
 *
 *  2. При c++20 и ниже: код успешно компилируется, но в runtime выбрасывается исключение:
 *                          terminate called after throwing an instance of 'std::logic_error'
 *                            what():  basic_string: construction from null is not valid
 *                          Aborted (core dumped)
 *
 * Поэтому явно прописана заглушка на случай std::nullptr_t, чтобы is_convertible_to_string возвращала false:
 */
template <>
struct is_convertible_to_string<std::nullptr_t> : std::false_type {};

template <typename T>
constexpr bool is_convertible_to_string_v = is_convertible_to_string<T>::value;

}  // namespace dev_toolkit::ucts::traits

#endif  // UNIVERSAL_CONVERTER_TO_STRING_TRAITS_H
