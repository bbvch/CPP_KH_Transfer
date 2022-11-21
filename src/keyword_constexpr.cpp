// SPDX-License-Identifier: GPL-3.0

#include <iostream>

/**
 * @brief constexpr is a feature added in C++ 11. The main idea is a performance improvement
 *  of programs by doing computations at compile time rather than run time. Note that once
 *  a program is compiled and finalized by the developer, it is run multiple times by users.
 *
 * RULE: If an expression is constexpr (calculated at compile time it can be used in static_assert
 *
 * What Follows: If you want to _force_ results at compile time, use static_assert!
 *
 *  constexpr function
 *   - Use constexpr function as much as you can
 *   - Every compiler since C++ 11 increases the supported features
 *
 *  constexpr user defined types
 *   - can not use exception handling
 *   - has to be declared default or delete constructors
 *
 *  constexpr values are stack values!
 *  you rarely want constexpr values!
 *         -  you almost always mean static constepxr instead!
 *
 * RULES: run all tests with address sanitizers (to catch errors of stack used after scope)
 *
 */

template <typename T> class NameByType {
    public:
    constexpr NameByType() = default;
    std::string to_string() {
        if constexpr (std::is_pointer<T>::value) {
        return "Pointer";
        } else if constexpr (std::is_integral<T>::value) {
        return "Integral";
        } else if constexpr (std::is_same<T, float>::value) {
        return "Float";
        } else {
        return "Unknown";
        }
    }
};

constexpr int double_value(int x) {
    return x*2;
}

int main(int, char **) {
    static constexpr int c{1000};

    // note that c is NOT captured (to prevent the warning 
    // "warning: capture of variable ‘c’ with non-automatic storage duration")
    const auto constexpr_func = [](int v) constexpr { return c + v; };

    return 0;
}