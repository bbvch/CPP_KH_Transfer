// SPDX-License-Identifier: GPL-3.0

/**
 * @brief Class template std::tuple is a fixed-size collection of heterogeneous values. It is a generalization of std::pair.
 *
 * It can be accessed via std::get and since C++17 via structured bindings. This helps to avoid boilerplate-code and
 * C-Style In/Out Parameter.
 */

#include <iostream>
#include <tuple>

std::tuple<bool, int, std::string> getNumberOfGrindersViaRpc(bool isConnected) {
    if(isConnected)
        return {true, 3, "Successful"};
    return {false, 0, "Not connected"};
}

int main(int, char **) {
    std::cout << std::boolalpha;
    auto resultOk = getNumberOfGrindersViaRpc(true);
    {
        std::cout << "\nFunction successfull: " << std::get<0>(resultOk);
        std::cout << "\nNumber of grinders: " << std::get<1>(resultOk);
        // this does not compile since there are only 0..2 available
        // std::cout << "\nError message: " << std::get<3>(resultOk);
    }
    // since C++17
    auto [successfull, numberOfGrinders, errorMessage] = getNumberOfGrindersViaRpc(false);
    {
        std::cout << "\nFunction successfull: " << successfull;
        std::cout << "\nError message: " << errorMessage;
    }
    std::cout << std::endl;
    return 0;
}