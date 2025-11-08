#include "universal_converter_to_string.h"

#include <iostream>
#include <cassert>

/*
template <typename T>
class MyClass {

    template <typename K>
    void displayTreeVertical(std::ostream& os, char emptySymbol, std::function<std::string(const T&)> = ) const {

        for (int level = 0; level < maxDepth(root); ++level) {
            setupLevel(level, os, emptySymbol);
            os << std::endl;
        }
    }

    // Настраивает длины отступов для уровней в зависимости от высоты дерева
    void BST::setupLevel(int n, std::ostream& os, char emptySymbol) const {




        //TODO: возможность выбирать scale/width для ширины поля вывода key, и сделать режим auto, чтобы выбиралось оптимальный размер на основе
        //TODO: вычисленной максимальной длины строки, хранящейся в данный момент в дереве.
        int indent = std::pow(2, (maxDepth(root) + 1) - n);
        os << std::setw(indent) << "";
        displayLevel(root, n, indent, os, emptySymbol);
    }

};
*/

int main() {
    {
        char val = 'A';
        auto result = dev_toolkit::universal_converter_to_string(val);
        assert(result.has_value());
        std::cout << result.value() << "  // ожидаем A" << std::endl;
        // assert(result.value() == "3.140000");
    }

    {
        unsigned char val = 'A';
        auto result = dev_toolkit::universal_converter_to_string(val);
        assert(result.has_value());
        std::cout << result.value() << "  // ожидаем A" << std::endl;
        // assert(result.value() == "3.140000");
    }

    return 0;
}