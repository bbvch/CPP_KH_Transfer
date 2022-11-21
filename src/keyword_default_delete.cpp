// SPDX-License-Identifier: GPL-3.0

#include <iostream>

/**
 * @brief A default constructor is a constructor which can be called
 *  with no arguments (either defined with an empty parameter list,
 *  or with default arguments provided for every parameter).
 *
 */

struct DefaultConstructible {
    DefaultConstructible() = default;

    std::string creator{"bbv"};
};

struct NonDefaultConstructible {
    NonDefaultConstructible() = delete;
    NonDefaultConstructible(std::string _creator) : creator(_creator) {
    }
    std::string creator;
};

struct DummyNonCopyable {
  DummyNonCopyable() = default;

  DummyNonCopyable(const DummyNonCopyable &) = delete;
  DummyNonCopyable &operator=(const DummyNonCopyable &rhs) = delete;
};

int main(int, char **) {
    std::cout << std::boolalpha
    << "DefaultConstructible: "
    << std::is_default_constructible<DefaultConstructible>::value
    << "\nNonDefaultConstructible: "
    << std::is_default_constructible<NonDefaultConstructible>::value
    << std::endl;

    DefaultConstructible defaultConstructible;
    NonDefaultConstructible nonDefaultConstructible("bbv");
    DummyNonCopyable A;

    // following line will not compile
    // DummyNonCopyable B = A;

    return 0;
}