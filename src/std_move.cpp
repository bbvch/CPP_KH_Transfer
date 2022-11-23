// SPDX-License-Identifier: GPL-3.0


/**
 * @brief std::move is used to indicate that an object t may be "moved from",
 *  i.e. allowing the efficient transfer of resources from t to another object.
 *
 * This is less expensive than copying it around.
 *
 * In particular, std::move produces an xvalue expression that identifies its argument t.
 * It is exactly equivalent to a static_cast to an rvalue reference type.
 *
 */

#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

int main()
{
    std::string str = "Salut";
    std::vector<std::string> v;

    // uses the push_back(const T&) overload, which means 
    // we'll incur the cost of copying str
    v.push_back(str);
    std::cout << "After copy, str is " << std::quoted(str) << '\n';

    // uses the rvalue reference push_back(T&&) overload, 
    // which means no strings will be copied; instead, the contents
    // of str will be moved into the vector.  This is less
    // expensive, but also means str might now be empty.
    v.push_back(std::move(str));
    std::cout << "After move, str is " << std::quoted(str) << '\n';

    std::cout << "The contents of the vector are { " << std::quoted(v[0])
                                             << ", " << std::quoted(v[1]) << " }\n";
}