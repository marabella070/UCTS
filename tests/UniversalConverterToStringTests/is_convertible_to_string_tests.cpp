#include "gtest/gtest.h"

#include "common_example_classes.h"
#include "is_convertible_to_string.h"

#include <deque>
#include <vector>

// --------------------- Tests itself ---------------------

TEST(is_convertible_to_string, supported_types_check) {
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<std::string>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<int>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<long>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<long long>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned long>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned long long>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<float>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<double>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<long double>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<const char*>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<std::string_view>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<std::initializer_list<char>>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<DerivedFromString>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<WithConvertOperator>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<DerivedFromStringWithConvertOperator>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<WithOutputOperator>);
}

TEST(is_convertible_to_string, additional_supported_types_check) {
    // is_to_string_compatible_v return true
    // because an implicit type conversion is being performed.
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<bool>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<char>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<signed char>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned char>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<short>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned char>);
    EXPECT_TRUE(dev_toolkit::is_convertible_to_string_v<unsigned short>);
}

TEST(is_convertible_to_string, not_supported_types_check) {
    EXPECT_FALSE(dev_toolkit::is_convertible_to_string_v<std::nullptr_t>); // Interesting extreme case.
    EXPECT_FALSE(dev_toolkit::is_convertible_to_string_v<void*>);
    EXPECT_FALSE(dev_toolkit::is_convertible_to_string_v<std::vector<int>>);
    EXPECT_FALSE(dev_toolkit::is_convertible_to_string_v<std::deque<std::string>>);
}

