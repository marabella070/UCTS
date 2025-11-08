#include "string_conversion_traits.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <cxxabi.h>

template<typename T>
std::string GetTypeName() {
    int status;
    std::string type_name = typeid(T).name();

    //TODO: директивой препроцессора явно прописать, что это работает только для gcc
    // https://stackoverflow.com/questions/1055452/c-get-name-of-type-in-template
    char *demangled_name = abi::__cxa_demangle(type_name.c_str(), NULL, NULL, &status);
    if(status == 0) {
        type_name = demangled_name;
        std::free(demangled_name);
    }   

    return type_name;
}

template <typename T>
struct StringConversionTraitsInfo {
    using type = T;
    static constexpr bool has_ostream_operator = string_conversion_traits::has_ostream_operator_v<T>;
    static constexpr bool has_to_string_conversion_operator = string_conversion_traits::has_to_string_conversion_operator_v<T>;
    static constexpr bool is_constructible = std::is_constructible_v<std::string, T>;
    static constexpr bool is_convertible_to_base = string_conversion_traits::is_convertible_to_base_v<std::string, T>;
    static constexpr bool is_to_string_compatible = string_conversion_traits::is_to_string_compatible_v<T>;

    static std::string GetInfo() {
        const size_t trait_width = 40;
        std::ostringstream oss;

        // Получаем имя типа
        std::string type_name = GetTypeName<type>();
        oss << "Type: " << type_name << "\n";
        
        oss << std::boolalpha;
        oss << std::setw(trait_width) << "has_ostream_operator - " << has_ostream_operator << '\n';
        oss << std::setw(trait_width) << "has_to_string_conversion_operator - " << has_to_string_conversion_operator << '\n';
        oss << std::setw(trait_width) << "is_constructible - " << is_constructible << '\n';
        oss << std::setw(trait_width) << "is_convertible_to_base - " << is_convertible_to_base << '\n';
        oss << std::setw(trait_width) << "is_to_string_compatible - " << is_to_string_compatible;

        return oss.str();
    }
};

template <typename T>
void PrintStringConversionTraits(std::ostream& os) {
    os << '\n' << StringConversionTraitsInfo<T>::GetInfo() << '\n';
}

template <typename... Types>
void PrintPackOfStringConversionTraitsInfo(std::ostream& os) {
    (... , PrintStringConversionTraits<Types>(os));
}

// -------------------------------- example types --------------------------------

class DerivedFromString : public std::string {};

struct WithConvertOperator {
    operator std::string() const { return "default"; }
};

// Пример для того, у чего выше приоритет:
class DerivedFromStringWithConvertOperator : public std::string {
    // В такой реализации НИКОГДА не будет вызван этот оператор:
    // И вероятно вообще не добавляется в сборку
    operator std::string() const { return "convert operator"; }
};

class WithOutputOperator
{
    friend std::ostream& operator<< (std::ostream& os, 
                                     const WithOutputOperator& withDefaultOutputOperator) { return os; }
};


int main() {
    std::ofstream regular_cases_info("string_conversion_traits_of_supported_types.txt");

    if (!regular_cases_info) {
        std::cerr << "Couldn't open the file for writing!" << std::endl;
        return 1;
    }
    
    // Определение всех трейтов для каждого из поддерживаемых типов:
    PrintPackOfStringConversionTraitsInfo<std::string,
                                          char, 
                                          signed char, 
                                          short, 
                                          int, 
                                          long, 
                                          long long, 
                                          unsigned char,
                                          unsigned short, 
                                          unsigned,
                                          unsigned long,
                                          unsigned long long,
                                          float, 
                                          double, 
                                          long double,
                                          const char*,
                                          std::string_view,
                                          std::initializer_list<char>,
                                          DerivedFromString,
                                          WithConvertOperator,
                                          DerivedFromStringWithConvertOperator,
                                          WithOutputOperator                    >(regular_cases_info);
    
    regular_cases_info.close();
    std::cout << "Information about the traits of the regular supported types has been successfully written to the file." << std::endl;

    return 0;
}