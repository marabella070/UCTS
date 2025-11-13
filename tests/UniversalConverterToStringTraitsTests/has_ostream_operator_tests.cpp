#include <deque>     // for deque
#include <iostream>  // for ostream, basic_ios
#include <string>    // for basic_string, string
#include <vector>    // for vector

#include "gtest/gtest.h"
#include "universal_converter_to_string_traits.h"  // for has_ostream_operat...

using namespace dev_toolkit::ucts::traits::details;

// ------------------------------------------------- Example Classes -------------------------------------------------

class WithoutOutputOperator {};

class WithDefaultOutputOperator {
    friend std::ostream& operator<<(std::ostream& os, const WithDefaultOutputOperator&) { return os; }
};

class WithOutputOperatorTakeValueByLvalueRef {
    // takes value by lvalue reference
    friend std::ostream& operator<<(std::ostream& os, WithOutputOperatorTakeValueByLvalueRef&) { return os; }
};

class WithOutputOperatorReturnVoid {
    // returns void
    friend void operator<<(std::ostream&, const WithOutputOperatorReturnVoid&) { /*return os;*/ }
};

// --------------------------------------------------- Tests itself ---------------------------------------------------

TEST(HasOstreamOperator, WithoutOutputOperatorCase) { EXPECT_FALSE(has_ostream_operator_v<WithoutOutputOperator>); }

TEST(HasOstreamOperator, WithDefaultOutputOperatorCase) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator>);
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator&>);
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator&&>);
}

TEST(HasOstreamOperator, WithOutputOperatorTakeValueByLvalueRefCase) {
    // Теперь результат зависит от типа переданной ссылки:
    EXPECT_FALSE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef&>);
    EXPECT_FALSE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef&&>);

    // Пример неудачного поиска стандартной сигнатуры:
    //  явно задаем шаблонный параметр как - [const T&]:
    EXPECT_FALSE(has_ostream_operator_v<const WithOutputOperatorTakeValueByLvalueRef&>);
}

TEST(HasOstreamOperator, WithOutputOperatorReturnVoidCase) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid&>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid&&>);

    WithOutputOperatorReturnVoid example;
    std::cout << example;  // OK
    // std::cout << example << std::endl; // CE
}

TEST(HasOstreamOperator, NotSupportedTypes) {
    EXPECT_FALSE(has_ostream_operator_v<std::nullptr_t>);
    EXPECT_FALSE(has_ostream_operator_v<void*>);
    EXPECT_FALSE(has_ostream_operator_v<std::vector<int>>);
    EXPECT_FALSE(has_ostream_operator_v<std::deque<std::string>>);
}
