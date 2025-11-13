#include <cxxabi.h>                                // for abi, __cxa_demangle
#include <cstdlib>                                 // for free, NULL, size_t
#include <fstream>                                 // for basic_ostream, ope...
#include <initializer_list>                        // for initializer_list
#include <iomanip>                                 // for operator<<, setw
#include <iostream>                                // for cerr, cout
#include <sstream>                                 // for basic_ostringstream
#include <string>                                  // for char_traits, basic...
#include <string_view>                             // for string_view
#include <typeinfo>                                // for type_info

#include "universal_converter_to_string_traits.h"  // for details

using namespace dev_toolkit::ucts::traits::details;

template <typename T>
std::string GetTypeName() {
    int status;
    std::string type_name = typeid(T).name();

    // TODO(marabella070): директивой препроцессора явно прописать, что это работает только для gcc
    //  https://stackoverflow.com/questions/1055452/c-get-name-of-type-in-template
    char* demangled_name = abi::__cxa_demangle(type_name.c_str(), NULL, NULL, &status);
    if (status == 0) {
        type_name = demangled_name;
        std::free(demangled_name);
    }

    return type_name;
}

template <typename T>
struct StringConversionTraitsInfo {
    using type = T;
    static constexpr bool has_ostream_operator = has_ostream_operator_v<T>;
    static constexpr bool has_to_string_conversion_operator = has_to_string_conversion_operator_v<T>;
    static constexpr bool is_constructible = std::is_constructible_v<std::string, T>;
    static constexpr bool is_convertible_to_base = is_convertible_to_base_v<std::string, T>;
    static constexpr bool is_to_string_compatible = is_to_string_compatible_v<T>;

    static std::string GetInfo() {
        const size_t trait_width = 40;
        std::ostringstream oss;

        // Получаем имя типа
        std::string type_name = GetTypeName<type>();
        oss << "Type: " << type_name << "\n";

        oss << std::boolalpha;
        oss << std::setw(trait_width) << "is_to_string_compatible - " << is_to_string_compatible << '\n';
        oss << std::setw(trait_width) << "is_constructible - " << is_constructible << '\n';
        oss << std::setw(trait_width) << "is_convertible_to_base - " << is_convertible_to_base << '\n';
        oss << std::setw(trait_width) << "has_to_string_conversion_operator - " << has_to_string_conversion_operator
            << '\n';
        oss << std::setw(trait_width) << "has_ostream_operator - " << has_ostream_operator;

        return oss.str();
    }
};

template <typename T>
void PrintStringConversionTraits(std::ostream& os) {
    os << '\n' << StringConversionTraitsInfo<T>::GetInfo() << '\n';
}

template <typename... Types>
void PrintPackOfStringConversionTraitsInfo(std::ostream& os) {
    (..., PrintStringConversionTraits<Types>(os));
}

// -------------------------------- example types --------------------------------

class DerivedFromString : public std::string {};

struct WithConvertOperator {
    operator std::string() const { return "default"; }
};

struct WithExplicitConvertOperator {
    explicit operator std::string() const { return "explicit"; }
};

// Пример у чего выше приоритет для конвертации:
class DerivedFromStringWithConvertOperator : public std::string {
    // will never use a type conversion operator [-Wclass-conversion]
    // Вероятно вообще не добавляется в сборку
    operator std::string() const { return "convert operator"; }
};

class WithOutputOperator {
    friend std::ostream& operator<<(std::ostream& os, const WithOutputOperator&) { return os; }
};

int main() {
    std::ofstream regular_cases_info("string_conversion_traits_of_supported_types.txt");

    if (!regular_cases_info) {
        std::cerr << "Couldn't open the file for writing!" << std::endl;
        return 1;
    }

    // Определение трейтов для каждого из поддерживаемых типов:
    PrintPackOfStringConversionTraitsInfo<std::string, char, signed char, short, int, long, long long, unsigned char,
                                          unsigned short, unsigned, unsigned long, unsigned long long, float, double,
                                          long double, bool, const char*, std::string_view, std::initializer_list<char>,
                                          DerivedFromString, WithConvertOperator, WithExplicitConvertOperator,
                                          DerivedFromStringWithConvertOperator, WithOutputOperator>(regular_cases_info);

    regular_cases_info.close();
    std::cout
        << "Information about the traits of the regular supported types has been successfully written to the file."
        << '\n';

    return 0;
}