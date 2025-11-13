#include <deque>             // for deque
#include <initializer_list>  // for initializer_list
#include <ostream>           // for operator<<, ostream, nullptr_t
#include <string>            // for basic_string, string
#include <string_view>       // for string_view
#include <type_traits>       // for is_constructible_v
#include <vector>            // for vector

#include "gtest/gtest.h"

// ------------------------------------------------- Example Classes -------------------------------------------------

class DerivedFromString : public std::string {};

struct WithConvertOperator {
    operator std::string() const { return "convert_operator"; }
};

struct WithExplicitConvertOperator {
    explicit operator std::string() const { return "explicit_convert_operator"; }
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

TEST(IsConstructible, CStrings) {
    EXPECT_TRUE((std::is_constructible_v<std::string, const char*>));

    // checking the possibility of a cast
    const char* c_str = "c string";
    std::string str_1 = static_cast<std::string>(c_str);
    EXPECT_STREQ(str_1.c_str(), "c string");

    char array[7] = {'a', 'r', 'r', 'a', 'y', '7', '\0'};
    std::string str_2 = static_cast<std::string>(array);
    EXPECT_STREQ(str_2.c_str(), "array7");
}

TEST(IsConstructible, StringWiewLike) {
    EXPECT_TRUE((std::is_constructible_v<std::string, std::string_view>));

    // checking the possibility of a cast
    std::string_view str_view = "string_view";
    std::string str_1 = static_cast<std::string>(str_view);
    EXPECT_STREQ(str_1.c_str(), "string_view");
}

TEST(IsConstructible, InitializerListChar) {
    EXPECT_TRUE((std::is_constructible_v<std::string, std::initializer_list<char>>));

    // checking the possibility of a cast
    std::initializer_list<char> init_list = {'i', 'n', 'i', 't', '_', 'l', 'i', 's', 't'};
    std::string str_1 = static_cast<std::string>(init_list);
    EXPECT_STREQ(str_1.c_str(), "init_list");
}

TEST(IsConstructible, NullptrT) {
    EXPECT_TRUE((std::is_constructible_v<std::string, std::nullptr_t>));

    // std::string str_1(nullptr); // после c++23 - CE, так как этот конструктор delete();

    // std::string str_2(nullptr); // до c++23 - исключение в runtime, так как std::string
    // не знает что значит создаться от nullptr.
}

TEST(IsConstructible, ImplicitlyConstructible) {
    EXPECT_TRUE((std::is_constructible_v<std::string, DerivedFromString>));
    EXPECT_TRUE((std::is_constructible_v<std::string, WithConvertOperator>));
    EXPECT_TRUE((std::is_constructible_v<std::string, WithExplicitConvertOperator>));  //! Interesting edge case.
    EXPECT_TRUE((std::is_constructible_v<std::string, DerivedFromStringWithConvertOperator>));
}

TEST(IsConstructible, NotSupportedTypes) {
    EXPECT_FALSE((std::is_constructible_v<std::string, WithOutputOperator>));
    EXPECT_FALSE((std::is_constructible_v<std::string, void*>));
    EXPECT_FALSE((std::is_constructible_v<std::string, std::vector<int>>));
    EXPECT_FALSE((std::is_constructible_v<std::string, std::deque<std::string>>));
}
