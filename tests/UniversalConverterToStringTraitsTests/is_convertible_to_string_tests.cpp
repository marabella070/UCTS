#include <deque>             // for deque
#include <initializer_list>  // for initializer_list
#include <ostream>           // for operator<<, ostream
#include <string>            // for basic_string, string
#include <string_view>       // for string_view
#include <vector>            // for vector

#include "gtest/gtest.h"
#include "universal_converter_to_string_traits.h"  // for is_convertible_to_...

using namespace dev_toolkit::ucts::traits;

#include <deque>
#include <vector>

// ------------------------------------------------- Example Classes -------------------------------------------------

class DerivedFromString : public std::string {};

struct WithConvertOperator {
    operator std::string() const { return "convert_operator"; }
};

struct WithExplicitConvertOperator {
    operator std::string() const { return "explicit"; }
};

class DerivedFromStringWithConvertOperator : public std::string {
    operator std::string() const { return "convert_operator"; }
};

class WithOutputOperator {
    friend std::ostream& operator<<(std::ostream& os, const WithOutputOperator&) {
        os << "output_operator";
        return os;
    }
};

// --------------------------------------------------- Tests itself ---------------------------------------------------

TEST(IsConvertibleToString, SupportedTypesCheck) {
    EXPECT_TRUE(is_convertible_to_string_v<std::string>);
    EXPECT_TRUE(is_convertible_to_string_v<int>);
    EXPECT_TRUE(is_convertible_to_string_v<long>);
    EXPECT_TRUE(is_convertible_to_string_v<long long>);
    EXPECT_TRUE(is_convertible_to_string_v<unsigned>);
    EXPECT_TRUE(is_convertible_to_string_v<unsigned long>);
    EXPECT_TRUE(is_convertible_to_string_v<unsigned long long>);
    EXPECT_TRUE(is_convertible_to_string_v<float>);
    EXPECT_TRUE(is_convertible_to_string_v<double>);
    EXPECT_TRUE(is_convertible_to_string_v<long double>);
    EXPECT_TRUE(is_convertible_to_string_v<const char*>);
    EXPECT_TRUE(is_convertible_to_string_v<std::string_view>);
    EXPECT_TRUE(is_convertible_to_string_v<std::initializer_list<char>>);
    EXPECT_TRUE(is_convertible_to_string_v<DerivedFromString>);
    EXPECT_TRUE(is_convertible_to_string_v<WithConvertOperator>);
    EXPECT_TRUE(is_convertible_to_string_v<WithExplicitConvertOperator>);
    EXPECT_TRUE(is_convertible_to_string_v<DerivedFromStringWithConvertOperator>);
    EXPECT_TRUE(is_convertible_to_string_v<WithOutputOperator>);
}

TEST(IsConvertibleToString, AdditionalSupportedTypesCheck) {
    // is_to_string_compatible_v return true
    // because an implicit type conversion is being performed.
    EXPECT_TRUE(is_convertible_to_string_v<bool>);
    EXPECT_TRUE(is_convertible_to_string_v<short>);
    EXPECT_TRUE(is_convertible_to_string_v<char>);
    EXPECT_TRUE(is_convertible_to_string_v<signed char>);
    EXPECT_TRUE(is_convertible_to_string_v<unsigned char>);
    EXPECT_TRUE(is_convertible_to_string_v<unsigned short>);
}

TEST(IsConvertibleToString, NotSupportedTypes) {
    EXPECT_FALSE(is_convertible_to_string_v<std::nullptr_t>);  // Interesting extreme case.
    EXPECT_FALSE(is_convertible_to_string_v<void*>);
    EXPECT_FALSE(is_convertible_to_string_v<std::vector<int>>);
    EXPECT_FALSE(is_convertible_to_string_v<std::deque<std::string>>);
}
