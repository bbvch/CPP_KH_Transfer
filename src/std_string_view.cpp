// SPDX-License-Identifier: GPL-3.0

#include <iostream>
#include <string>
#include <string_view>

/**
 * @brief Comparisons of memory access between string_view and string.
 *
 * For a better understanding the new operator is overriden such that a message is output for every heap allocation.
 *
 * A string_view is a representation pointing to the begin end end of a string, thus not allocating itself.
 * As a result using string:view will yield in a significant smaller dynamic memory usage.
 */


void* operator new(std::size_t count){
    std::cout << "\n   " << count << " bytes" << std::endl;
    return malloc(count);
}

int getLengthSv(std::string_view sv) {
    return sv.length();
}

int getLengthStr(const std::string& str) {
    return str.length();
}

struct ComponentSv {
    public:
        ComponentSv(std::string_view _name)
         : name(_name) {
        }
        std::string_view getName() {
            return name;
        }
        void setName(std::string_view _name)
        {
            name = _name;
        }
    private:
    std::string_view name;
};

struct ComponentStr {
    public:
        ComponentStr(const std::string& _name)
         : name(_name) {
         }
        std::string getName() {
            return name;
        }
        void setName(const std::string& _name)
        {
            name = _name;
        }
    private:
    std::string name;
};

int main(int, char **) {
    {
        std::cout << "\n\n\n>>>>>>>>>>>>>>>>>>> std::string_view >>>>>>" << std::endl;
        std::cout << "Length of \"I Like Coffee\":" << getLengthSv("I Like Coffee") << "\n";
        constexpr std::string_view constexpr_sv("Hello constexpr world!");
        ComponentSv A("BrewerSv");
        std::cout << "My name is " << A.getName() << std::endl;
        std::string_view grinderName("ThisIsARatherLongStringWhichCannotBeOptimizedEasily");
        A.setName(grinderName);
        std::cout << "My name is " << A.getName() << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<<< std::string_view <<<<<<\n\n\n" << std::endl;
    }
    {
        std::cout << ">>>>>>>>>>>>>>>>>>> std::string >>>>>>" << std::endl;
        std::cout << "Length of \"I Like Coffee\":" << getLengthStr("I Like Coffee") << "\n";
        std::string str("Hello constexpr world!");
        ComponentStr A("BrewerStr");
        std::cout << "My name is " << A.getName() << std::endl;
        std::string grinderName("ThisIsARatherLongStringWhichCannotBeOptimizedEasily");
        A.setName(grinderName);
        std::cout << "My name is " << A.getName() << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<<< std::string <<<<<<\n\n\n" << std::endl;
    }

    return 0;
}