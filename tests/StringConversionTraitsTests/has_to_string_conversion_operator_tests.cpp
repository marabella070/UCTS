#include "gtest/gtest.h"

#include "string_conversion_traits.h"

using namespace string_conversion_traits;

// --------------------- Example Classes ---------------------

struct WithoutConvertOperator {};

struct WithDefaultConvertOperator {
    operator std::string() const { return "default"; }
};

struct WithRefQualifiedConvertOperator {
    operator std::string() & { return "1"; }

    operator std::string() && { return "2"; }
};


// --------------------- Tests itself ---------------------

TEST(has_to_string_conversion_operator, without_convert_operator) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator&>);
    EXPECT_FALSE(has_to_string_conversion_operator_v<WithoutConvertOperator&&>);
}

TEST(has_to_string_conversion_operator, with_default_convert_operator) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator&>);
    EXPECT_TRUE(has_to_string_conversion_operator_v<WithDefaultConvertOperator&&>);
}

TEST(has_to_string_conversion_operator, with_ref_qualified_convert_operator) {
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
        std::string result_2 = static_cast<std::string>(std::move(obj)); // 2
        EXPECT_STREQ(result_2.c_str(), "2");
    }
}

