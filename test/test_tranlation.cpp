#include <gtest.h>
#include "tranlation.h"

TEST(ArithmeticExpression, can_add_whole_numbers) {
    ArithmeticExpression expression("3 + 10 + 3 + 7");
    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 3 + 10 + 3 + 7;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_subtract_whole_numbers) {
    ArithmeticExpression expression("10 - 8 - (-3) - 5");
    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 10 - 8 - (-3) - 5;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_multiply_whole_numbers) {
    ArithmeticExpression expression("2 * 10 * 3 * 1");

    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 2 * 10 * 3 * 1;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_add_real_numbers) {
    ArithmeticExpression expression("3.5 + 10.2 + 3.7 + 7.3");
    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 3.5 + 10.2 + 3.7 + 7.3;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_subtract_real_numbers) {
    ArithmeticExpression expression("10.2 - 8.7 - (-3.9) - 5.2");
    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 10.2 - 8.7 - (-3.9) - 5.2;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_multiply_real_numbers) {
    ArithmeticExpression expression("2.6 * 10.3 * 3.2 * 1.8");

    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 2.6 * 10.3 * 3.2 * 1.8;

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, can_divide_real_numbers) {
    ArithmeticExpression expression("3.2 / 5.5 / (9.8 / 5.6)");
    std::ostream nowhere(nullptr);

    double result = expression.Calculate(std::cin, nowhere);
    double expected = 3.2 / 5.5 / (9.8 / 5.6);

    EXPECT_EQ(expected, result);
}
TEST(ArithmeticExpression, new_test) {
    ArithmeticExpression expression("2 * ");
    std::ostream nowhere(nullptr);

    EXPECT_ANY_THROW(expression.Calculate(std::cin, nowhere));
}