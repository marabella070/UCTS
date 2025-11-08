#ifndef COMMON_EXAMPLE_CLASSES
#define COMMON_EXAMPLE_CLASSES

#include <string>

// --------------------- Common Example Classes ---------------------

class DerivedFromString : public std::string {};

struct WithConvertOperator {
    operator std::string() const { return "convert_operator"; }
};

class DerivedFromStringWithConvertOperator : public std::string {
    operator std::string() const { return "convert_operator"; }
};

class WithOutputOperator
{
    friend std::ostream& operator<< (std::ostream& os, 
                                     const WithOutputOperator& withDefaultOutputOperator) { 
        os << "output_operator";
        return os; 
    }
};

#endif // COMMON_EXAMPLE_CLASSES

