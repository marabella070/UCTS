#include "gtest/gtest.h"

#include "string_conversion_traits.h"

using namespace string_conversion_traits;

// --------------------- Example Classes ---------------------

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


// --------------------- Tests itself ---------------------

TEST(is_convertible_to_base, public_inheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, PublicInheritanceFromString>));
    EXPECT_TRUE((is_convertible_to_base_v<std::string, PublicInheritanceFromString>));
    
    PublicInheritanceFromString derived_from_string;
    std::string str = static_cast<std::string>(derived_from_string); // can be casted
}

TEST(is_convertible_to_base, private_inheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, PrivateInheritanceFromString>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, PrivateInheritanceFromString>));

    PrivateInheritanceFromString derived_from_string;
    //! std::string str = static_cast<std::string>(derived_from_string); - can't be casted!
}

TEST(is_convertible_to_base, protected_inheritance) {
    // comparing behavior between functions
    EXPECT_TRUE((std::is_base_of_v<std::string, ProtectedInheritanceFromString>));
    EXPECT_FALSE((is_convertible_to_base_v<std::string, ProtectedInheritanceFromString>));

    ProtectedInheritanceFromString derived_from_string;
    //! std::string str = static_cast<std::string>(derived_from_string); - can't be casted!
}

TEST(is_convertible_to_base, raising_cast_is_not_allowed) {
    EXPECT_FALSE((is_convertible_to_base_v<Mother, Granny>)); // Not supported
    EXPECT_TRUE((is_convertible_to_base_v<Mother, Daughter>)); // OK
}

TEST(is_convertible_to_base, inheritance_with_convert_operator) {
    DerivedFromStringWithConvertOperator obj;
    std::string str = static_cast<std::string>(obj);
    EXPECT_STRNE(str.c_str(), "convert operator");
    EXPECT_STREQ(str.c_str(), "");
}

