#include "example.hpp" // Include our Calculator header
#include <iostream>    // For console output

/**
 * @brief The main entry point of the cpp-template application.
 *
 * This function demonstrates the usage of the Calculator class.
 * It performs a simple addition and subtraction operation and prints the results.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return 0 if the program executes successfully, non-zero otherwise.
 */
int main()
{
    Calculator calc;

    int num1 = 10;
    int num2 = 5;

    int sum = calc.add(num1, num2);
    int difference = calc.subtract(num1, num2);

    std::cout << "Using Calculator:" << std::endl;
    std::cout << num1 << " + " << num2 << " = " << sum << std::endl;
    std::cout << num1 << " - " << num2 << " = " << difference << std::endl;

    return 0;
}
