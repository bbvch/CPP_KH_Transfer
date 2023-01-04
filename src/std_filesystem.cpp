#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    fs::path tmp{"/tmp"};
    if (!fs::exists(tmp)) {
        std::cout << "/tmp does not exist" << std::endl;
        return 0;
    }

    const bool result = fs::create_directories(tmp);
    if (!result) {
        std::cout << "Could not create tmp dir" << std::endl;
    }

    for (auto const& dir_entry : fs::directory_iterator(tmp)) {
        if (dir_entry.is_directory()) {
            // ...
        }
    }

    if (fs::is_directory(tmp)) {
        // ...
    }
}