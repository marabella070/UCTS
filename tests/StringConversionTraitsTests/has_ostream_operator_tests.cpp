#include "gtest/gtest.h"

#include "string_conversion_traits.h"

using namespace string_conversion_traits;

// --------------------- Example Classes ---------------------

class WithoutOutputOperator {};

class WithDefaultOutputOperator
{
    friend std::ostream& operator<< (std::ostream& os, const WithDefaultOutputOperator& withDefaultOutputOperator) { return os; }
};

class WithOutputOperatorTakeValueByLvalueRef {
    // takes value by lvalue reference
    friend std::ostream& operator<< (std::ostream& os, WithOutputOperatorTakeValueByLvalueRef& withOutputOperatorTakeValueByLvalueRef) { return os; }
};

class WithOutputOperatorReturnVoid {
    // returns void
    friend void operator<< (std::ostream& os, const WithOutputOperatorReturnVoid& withOutputOperatorReturnVoid) { /*return os;*/ }
};


// --------------------- Tests itself ---------------------

TEST(has_ostream_operator, without_output_operator) {
    EXPECT_FALSE(has_ostream_operator_v<WithoutOutputOperator>);
}

TEST(has_ostream_operator, with_default_output_operator) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator>);
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator&>);
    EXPECT_TRUE(has_ostream_operator_v<WithDefaultOutputOperator&&>);
}

TEST(has_ostream_operator, with_output_operator_that_take_value_by_lvalue_reference) {
    // Теперь результат зависит от типа переданной ссылки:
    EXPECT_FALSE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef&>);
    EXPECT_FALSE(has_ostream_operator_v<WithOutputOperatorTakeValueByLvalueRef&&>);

    // Пример неудачного поиска стандартной сигнатуры:
    //  явно задаем шаблонный параметр как - [const T&]:
    EXPECT_FALSE(has_ostream_operator_v<const WithOutputOperatorTakeValueByLvalueRef&>);
}

TEST(has_ostream_operator, with_output_operator_that_return_void) {
    // Результат не зависит от типа переданной ссылки:
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid&>);
    EXPECT_TRUE(has_ostream_operator_v<WithOutputOperatorReturnVoid&&>);
    
    WithOutputOperatorReturnVoid example;
    std::cout << example; // OK
    // std::cout << example << std::endl; // CE
}

