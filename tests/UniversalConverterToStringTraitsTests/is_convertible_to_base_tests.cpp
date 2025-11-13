#include <deque>        // for deque
#include <iosfwd>       // for nullptr_t
#include <string>       // for basic_string, string
#include <type_traits>  // for is_base_of_v
#include <vector>       // for vector

#include "gtest/gtest.h"
#include "universal_converter_to_string_traits.h"  // for is_convertible_to_...

using namespace dev_toolkit::ucts::traits::details;

// ------------------------------------------------- Example Classes -------------------------------------------------

class PublicInheritanceFromString : public std::string {};

class PrivateInheritanceFromString : private std::string {};

class ProtectedInheritanceFromString : protected std::string {};

class DerivedFromStringWithConvertOperator : public std::string {
    //! В этом случае НИКОГДА не будет вызван этот оператор:
    operator std::string() const { return "convert operator"; }
};

// inheritance hierarchy
class Granny {};

class Mother : public Granny {};

class Daughter : public Mother {};

// --------------------------------------------------- Tests itself ---------------------------------------------------

TEST(IsConvertibleToBase, PublicInheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, PublicInheritanceFromString>));
    EXPECT_TRUE((is_convertible_to_base_v<std::string, PublicInheritanceFromString>));

    PublicInheritanceFromString derived_from_string;
    std::string str = static_cast<std::string>(derived_from_string);  // can be casted
}

TEST(IsConvertibleToBase, PrivateInheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, PrivateInheritanceFromString>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, PrivateInheritanceFromString>));

    PrivateInheritanceFromString derived_from_string;
    //! std::string str = static_cast<std::string>(derived_from_string); - can't be casted!
}

TEST(IsConvertibleToBase, ProtectedInheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, ProtectedInheritanceFromString>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, ProtectedInheritanceFromString>));

    ProtectedInheritanceFromString derived_from_string;
    //! std::string str = static_cast<std::string>(derived_from_string); - can't be casted!
}

TEST(IsConvertibleToBase, RaisingCastIsNotAllowed) {
    EXPECT_FALSE((is_convertible_to_base_v<Mother, Granny>));   // Not supported
    EXPECT_TRUE((is_convertible_to_base_v<Mother, Daughter>));  // OK
}

TEST(IsConvertibleToBase, InheritanceWithConvertOperator) {
    DerivedFromStringWithConvertOperator obj;
    std::string str = static_cast<std::string>(obj);
    EXPECT_STRNE(str.c_str(), "convert operator");
    EXPECT_STREQ(str.c_str(), "");
}

TEST(IsConvertibleToBase, NotSupportedTypes) {
    EXPECT_FALSE((is_convertible_to_base_v<std::string, std::nullptr_t>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, void*>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, std::vector<int>>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, std::deque<std::string>>));
}
