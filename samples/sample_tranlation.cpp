#include <iostream>
#include <string>
#include "tranlation.h"

int main() {

    std::string str;

    std::cout << "Enter an arithmetic expression: ";
    std::cin >> str;
    ArithmeticExpression expression(str);

    double res = expression.Calculate();
    std::cout << "Result: " << res << std::endl;

    return 0;
}
//jopa