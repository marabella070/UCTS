#include "gtest/gtest.h"

#include "string_conversion_traits.h"

using namespace string_conversion_traits;

// --------------------- Tests itself ---------------------

TEST(is_to_string_compatible, different_ref_types) {
    // Для стандартных типов, результат не зависит от типа переданной ссылки
    EXPECT_TRUE(is_to_string_compatible_v<int&>);
    EXPECT_TRUE(is_to_string_compatible_v<const int&>);
    EXPECT_TRUE(is_to_string_compatible_v<int>);
    EXPECT_TRUE(is_to_string_compatible_v<int&&>);
}

TEST(is_to_string_compatible, all_supported_types) {
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

