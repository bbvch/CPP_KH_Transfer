// SPDX-License-Identifier: GPL-3.0

#include <iostream>
#include <set>

std::set<std::string> getMyStringList()
{
    return {"I", "like", "coffee", "machines"};
}

int main(int, char **) {
    // since C++17
    // same goes for switch/case statements
    if(auto stringList = getMyStringList();
     stringList.find(std::string("coffee")) != stringList.end())
    {
        std::cout << "Found some coffee" << std::endl;
    }

    // since C++20
    for(auto stringList = getMyStringList(); const auto& stringVal : stringList)
    {
        std::cout << stringVal << std::endl;
    }
    return 0;
}