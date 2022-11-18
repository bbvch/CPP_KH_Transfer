// SPDX-License-Identifier: GPL-3.0

/*

This example is about attributes:
 - [[fallthrough]]
 - [[unlikely]]
 - [[deprecated]]

**/

#include <iostream>
#include <ctime>

int getDayOfTheWeek() {
    std::tm time_in = { 0, 0, 0, // second, minute, hour
        9, 10, 2016 - 1900 }; // 1-based day, 0-based month, year since 1900

    std::time_t time_temp = std::mktime(&time_in);
    const std::tm * time_out = std::localtime(&time_temp);
    return time_out->tm_wday;
}

void example_fallthrough() {
    std::cout << "example_fallthrough" << std::endl;
    /**
     * @brief Indicates that the fall through from the previous case label is intentional
     *  and should not be diagnosed by a compiler that warns on fallthrough.
     *
     * since C++17
     */
    auto dayOfTheWeek = getDayOfTheWeek();

    switch (dayOfTheWeek) {
        case 0:     [[fallthrough]];
        case 6:
            std::cout << "It's weekend, shut down your computer!" << std::endl;
            break;
        case 1:     [[fallthrough]];
        case 2:     [[fallthrough]];
        case 3:     [[fallthrough]];
        case 4:     [[fallthrough]];
        case 5:
            std::cout << "Keep on working until it's weekend!" << std::endl;
            break;
        default:
            std::cout << "What day is it actually?" << std::endl;
            break;
    }
}

void example_unlikely() {
    /**
     * @brief Allow the compiler to optimize for the case where paths of execution including
     *  that statement are more or less likely than any alternative path of execution that
     *  does not include such a statement
     *
     * since C++17
     */
    std::cout << "example_unlikely" << std::endl;
    auto dayOfTheWeek = getDayOfTheWeek();
    if(dayOfTheWeek == 0) [[unlikely]]
    {
        std::cout << "Do not work on sundays!" << std::endl;
    }
    if(dayOfTheWeek > 0 && dayOfTheWeek < 6) [[likely]]
    {
        std::cout << "Keep on working until it's weekend!" << std::endl;
    }
    return;
}

namespace [[deprecated("Use function doubleItC++20 instead!")]] legacy {
    /**
     * @brief Indicates that the name or entity declared with this attribute is deprecated,
     *  that is, the use is allowed, but discouraged for some reason.
     *
     * @param x
     * @return int
     *
     * since C++14
     */
    int doubleIt(int x) {
        return x*2;
    }
}

void example_deprecated() {
    std::cout << "example_deprecated" << std::endl;
    std::cout << legacy::doubleIt(1 << 30) << std::endl;
}

int main(int, char **) {
    example_fallthrough();
    example_unlikely();
    example_deprecated();
    return 0;
}