#ifndef CPP_TEMPLATE_CALCULATOR_HPP
#define CPP_TEMPLATE_CALCULATOR_HPP

/**
 * @brief A simple calculator class for basic arithmetic operations.
 *
 * This class provides methods to perform addition and subtraction.
 * It serves as an example for how to structure a class in the `include` directory
 * and how to document it using Doxygen.
 */
class Calculator
{
  public:
    /**
     * @brief Adds two integers and returns the sum.
     * @param a The first integer.
     * @param b The second integer.
     * @return The sum of `a` and `b`.
     */
    int add(int a, int b);

    /**
     * @brief Subtracts the second integer from the first.
     * @param a The first integer (minuend).
     * @param b The second integer (subtrahend).
     * @return The result of `a - b`.
     */
    int subtract(int a, int b);
};

#endif // CPP_TEMPLATE_CALCULATOR_HPP
