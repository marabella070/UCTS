#include "gtest/gtest.h"

// #include <type_traits>
// #include <string>
// #include <string_view>

// --------------------- Tests itself ---------------------

TEST(is_constructible, c_strings) {
    EXPECT_TRUE((std::is_constructible_v<std::string, const char*>));

    // checking the possibility of a cast
    const char* c_str = "c string";
    std::string str_1 = static_cast<std::string>(c_str);
    EXPECT_STREQ(str_1.c_str(), "c string");

    char array[6] = {'a', 'r', 'r', 'a', 'y', '6', };
    std::string str_2 = static_cast<std::string>(array);
    EXPECT_STREQ(str_2.c_str(), "array6");
}

TEST(is_constructible, string_view_like) {
    EXPECT_TRUE((std::is_constructible_v<std::string, std::string_view>));

    // checking the possibility of a cast
    std::string_view str_view = "string_view";
    std::string str_1 = static_cast<std::string>(str_view);
    EXPECT_STREQ(str_1.c_str(), "string_view");
}

TEST(is_constructible, initializer_list_char) {
    EXPECT_TRUE((std::is_constructible_v<std::string, std::initializer_list<char>>));

    // checking the possibility of a cast
    std::initializer_list<char> init_list = {'i', 'n', 'i', 't', '_', 'l', 'i', 's', 't' };
    std::string str_1 = static_cast<std::string>(init_list);
    EXPECT_STREQ(str_1.c_str(), "init_list");
}

