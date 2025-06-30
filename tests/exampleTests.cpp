#include "example.hpp"                  // Your Calculator class
#include <catch2/catch_session.hpp>     // This provides the main() implementation
#include <catch2/catch_test_macros.hpp> // This provides TEST_CASE, REQUIRE, etc.

/**
 * @brief Test case for the Calculator::add method.
 *
 * This test verifies the correct addition functionality of the Calculator class
 * for various input scenarios, including positive numbers, zeros, and negative numbers.
 */
TEST_CASE("Calculator::add adds two numbers correctly", "[Calculator][add]")
{
    Calculator calc;

    // Test positive numbers
    REQUIRE(calc.add(2, 3) == 5);
    REQUIRE(calc.add(10, 20) == 30);

    // Test with zero
    REQUIRE(calc.add(5, 0) == 5);
    REQUIRE(calc.add(0, 0) == 0);

    // Test with negative numbers
    REQUIRE(calc.add(-2, -3) == -5);
    REQUIRE(calc.add(2, -3) == -1);
    REQUIRE(calc.add(-2, 3) == 1);
}

/**
 * @brief Test case for the Calculator::subtract method.
 *
 * This test verifies the correct subtraction functionality of the Calculator class
 * for various input scenarios, including positive numbers, zeros, and negative numbers.
 */
TEST_CASE("Calculator::subtract subtracts two numbers correctly", "[Calculator][subtract]")
{
    Calculator calc;

    // Test positive numbers
    REQUIRE(calc.subtract(5, 2) == 3);
    REQUIRE(calc.subtract(10, 20) == -10);

    // Test with zero
    REQUIRE(calc.subtract(5, 0) == 5);
    REQUIRE(calc.subtract(0, 0) == 0);

    // Test with negative numbers
    REQUIRE(calc.subtract(-5, -2) == -3);
    REQUIRE(calc.subtract(2, -3) == 5);
    REQUIRE(calc.subtract(-2, 3) == -5);
}
