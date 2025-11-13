#include <string>  // for basic_string

#include "gtest/gtest.h"
#include "universal_converter_to_string_traits.h"  // for is_to_string_compa...

using namespace dev_toolkit::ucts::traits::details;

// --------------------------------------------------- Tests itself ---------------------------------------------------

TEST(IsToStringCompatible, DifferentRefTypes) {
    // Для стандартных типов, результат не зависит от типа переданной ссылки
    EXPECT_TRUE(is_to_string_compatible_v<int&>);
    EXPECT_TRUE(is_to_string_compatible_v<const int&>);
    EXPECT_TRUE(is_to_string_compatible_v<int>);
    EXPECT_TRUE(is_to_string_compatible_v<int&&>);
}

TEST(IsToStringCompatible, ExplicitlySupportedTypes) {
    EXPECT_TRUE(is_to_string_compatible_v<int>);
    EXPECT_TRUE(is_to_string_compatible_v<long>);
    EXPECT_TRUE(is_to_string_compatible_v<long long>);
    EXPECT_TRUE(is_to_string_compatible_v<unsigned>);
    EXPECT_TRUE(is_to_string_compatible_v<unsigned long>);
    EXPECT_TRUE(is_to_string_compatible_v<unsigned long long>);
    EXPECT_TRUE(is_to_string_compatible_v<float>);
    EXPECT_TRUE(is_to_string_compatible_v<double>);
    EXPECT_TRUE(is_to_string_compatible_v<long double>);
}

TEST(IsToStringCompatible, ImplicitlySupportedTypes) {
    EXPECT_TRUE(is_to_string_compatible_v<char>);
    EXPECT_TRUE(is_to_string_compatible_v<signed char>);
    EXPECT_TRUE(is_to_string_compatible_v<short>);
    EXPECT_TRUE(is_to_string_compatible_v<unsigned char>);
    EXPECT_TRUE(is_to_string_compatible_v<unsigned short>);
    EXPECT_TRUE(is_to_string_compatible_v<bool>);
}
