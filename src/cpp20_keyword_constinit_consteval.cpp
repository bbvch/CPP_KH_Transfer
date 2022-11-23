// SPDX-License-Identifier: GPL-3.0

#include <iostream>

/**
 * @brief
 * https://stackoverflow.com/questions/57845131/what-is-constinit-in-c20
 * use constinit to avoid the "static initialization order fiasco"
 * it should be applied on variables with static storage duration.
 * If the decorated variable is not initialized at compile-time, the program is ill-formed.
 *
 * constexpr does imply constinit.
 *
 * consteval functions are immediate functions. they can be use to eliminate preprocessor macros.
 * They must be evaluated at compile time and produce a constant.
 */

// OK, initialized at compile-time
constinit auto GlobalPhrase = "Work's fine";
constinit int const_init_fourty_two = 42;

// Immediate Function, requires compile-time constants
consteval int square(int n) {
 return n*n;
}

struct CompileTimeInt {
    consteval CompileTimeInt(int v) : value(v) {}
    const int value;
};


int main(int, char **) {
    // OK
    int square1 = square(10);

    // OK
    constexpr int constexpr_ten = 10;
    int square2 = square(constexpr_ten);

    // OK
    const int const_ten = 10;
    int square3 = square(const_ten);

    // Error: call to square is not a constant expression
    int ten = 10;
    // int square4 = square(ten);

    const int const_fourty_two = 42;

    // Error: call to CompileTimeInt is not a constant expression
    // CompileTimeInt FourtyTwo(const_init_fourty_two);

    // OK
    CompileTimeInt FourtyTwo(const_fourty_two);

    return 0;
}