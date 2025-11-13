#include <deque>    // for deque
#include <iosfwd>   // for nullptr_t
#include <string>   // for basic_string, string
#include <utility>  // for move
#include <vector>   // for vector

#include "gtest/gtest.h"
#include "universal_converter_to_string_traits.h"  // for has_to_string_conv...

using namespace dev_toolkit::ucts::traits::details;

// ------------------------------------------------- Example Classes -------------------------------------------------

struct WithoutConvertOperator {};

struct WithDefaultConvertOperator {
    operator std::string() const { return "default"; }
};

struct WithExplicitConvertOperator {
    operator std::string() const { return "explicit"; }
};

struct WithRefQualifiedConvertOperator {
    operator std::string() & { return "1"; }

    operator std::string() && { return "2"; }
};

// --------------------------------------------------- Tests itself ---------------------------------------------------

TEST(HasToStringConversionOperator, WithoutConvertOperatorCase) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator&>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator&&>);
}

TEST(HasToStringConversionOperator, WithDefaultConvertOperatorCase) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator&>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator&&>);
}

TEST(HasToStringConversionOperator, WithExplicitConvertOperatorCase) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithExplicitConvertOperator>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithExplicitConvertOperator&>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithExplicitConvertOperator&&>);
}

TEST(HasToStringConversionOperator, WithRefQualifiedConvertOperatorCase) {
    //! В данном случае результат зависит от типа переданной ссылки:

    WithRefQualifiedConvertOperator obj;

    // lvalue case:
    {
        EXPECT_TRUE(has_to_string_conversion_operator_v<WithRefQualifiedConvertOperator&>);
        std::string result_1 = static_cast<std::string>(obj);
        EXPECT_STREQ(result_1.c_str(), "1");
    }

    // rvalue case:
    {
        EXPECT_TRUE(has_to_string_conversion_operator_v<WithRefQualifiedConvertOperator&&>);
        std::string result_2 = static_cast<std::string>(std::move(obj));  // 2
        EXPECT_STREQ(result_2.c_str(), "2");
    }
}

TEST(HasToStringConversionOperator, NotSupportedTypes) {
    EXPECT_FALSE(has_to_string_conversion_operator_v<std::nullptr_t>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<void*>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<std::vector<int>>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<std::deque<std::string>>);
}
