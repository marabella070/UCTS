#include "gtest/gtest.h"

#include "common_example_classes.h"
#include "universal_converter_to_string.h"

#include <variant>
#include <string_view>

// ----------------------------------------- Tests itself -----------------------------------------

template <typename T>
bool test_conversion(T&& initial_value, const std::string& expected_value) {
    auto result = dev_toolkit::universal_converter_to_string(std::forward<T>(initial_value));
    if (!result.has_value()) { return false; }
    return result.value() == expected_value;
}

TEST(UniversalConverterTest, DegenerateCase) {
    EXPECT_TRUE(test_conversion(static_cast<std::string>("std::string"), "std::string"));   // std::string
}

TEST(UniversalConverterTest, IntegerTypes) {
    EXPECT_TRUE(test_conversion(static_cast<char>('A'), "A"));                                        //! char, pay attention, result is "A"!
    EXPECT_TRUE(test_conversion(static_cast<signed char>(65), "65"));                                 // signed short
    EXPECT_TRUE(test_conversion(static_cast<short>(100), "100"));                                     // short
    EXPECT_TRUE(test_conversion(static_cast<int>(42), "42"));                                         // int
    EXPECT_TRUE(test_conversion(static_cast<long>(1000L), "1000"));                                   // long
    EXPECT_TRUE(test_conversion(static_cast<long long>(123456789LL), "123456789"));                   // long long

    EXPECT_TRUE(test_conversion(static_cast<unsigned char>('a'), "a"));                               //! unsigned char, pay attention, result is "a"!
    EXPECT_TRUE(test_conversion(static_cast<unsigned short>(500), "500"));                            // unsigned short
    EXPECT_TRUE(test_conversion(static_cast<unsigned>(100U), "100"));                                 // unsigned
    EXPECT_TRUE(test_conversion(static_cast<unsigned long>(5000UL), "5000"));                         // unsigned long
    EXPECT_TRUE(test_conversion(static_cast<unsigned long long>(123456789012ULL), "123456789012"));   // unsigned long long
}

TEST(UniversalConverterTest, FloatingPointTypesBasic) {
    EXPECT_TRUE(test_conversion(static_cast<float>(3.14f), "3.140000"));        // float
    EXPECT_TRUE(test_conversion(static_cast<double>(3.14), "3.140000"));        // double
    EXPECT_TRUE(test_conversion(static_cast<long double>(3.14L), "3.140000"));  // long double
}

TEST(UniversalConverterTest, FloatingPointTypesExtremes) {
    EXPECT_TRUE(test_conversion(static_cast<double>(-3.14), "-3.140000"));                  // negative_number - добавляет шесть нулей
    EXPECT_TRUE(test_conversion(static_cast<double>(3.0), "3.000000"));                     // integer_in_double - добавляет .000000
    EXPECT_TRUE(test_conversion(static_cast<double>(123456789.0), "123456789.000000"));     // large_number - формат без экспоненты, с шестью знаками
    EXPECT_TRUE(test_conversion(static_cast<double>(-987654.321), "-987654.321000"));       // large_negative_number - same
    EXPECT_TRUE(test_conversion(static_cast<double>(3.0000001), "3.000000"));               // little_over_then_inteher - округляется в пределах 6 знаков
    EXPECT_TRUE(test_conversion(static_cast<double>(2.9999999), "3.000000"));               // almost_integer - округление вверх
    EXPECT_TRUE(test_conversion(static_cast<double>(0.0000012345), "0.000001"));            // small_number - обрезается до шести знаков после запятой
    EXPECT_TRUE(test_conversion(static_cast<double>(0.0000000001), "0.000000"));            // almost_zero - same
}

TEST(UniversalConverterTest, BooleanType) {
    // Результат представляет собой строковое представление bool, а не целочисленное представление
    EXPECT_TRUE(test_conversion(static_cast<bool>(true), "true"));
    EXPECT_TRUE(test_conversion(static_cast<bool>(false), "false"));
}

TEST(UniversalConverterTest, ConstructibleTypes) {
    EXPECT_TRUE(test_conversion(static_cast<const char*>("c_string"), "c_string"));                 // const char*
    EXPECT_TRUE(test_conversion(static_cast<std::string_view>("string_view"), "string_view"));      // std::string_view

    std::initializer_list<char> init_list = {'i', 'n', 'i', 't', 'i', 'a', 'l', 'i', 'z', 'e', 'r', 
                                                '_', 'l', 'i', 's', 't' };
    EXPECT_TRUE(test_conversion(init_list, "initializer_list"));                                    // std::initializer_list<char>
}

TEST(UniversalConverterTest, SpecialConstructibleTypes) {
    EXPECT_TRUE(test_conversion(DerivedFromString(), ""));
    EXPECT_TRUE(test_conversion(WithConvertOperator(), "convert_operator"));
    EXPECT_TRUE(test_conversion(DerivedFromStringWithConvertOperator(), ""));
    EXPECT_TRUE(test_conversion(WithOutputOperator(), "output_operator"));
}

