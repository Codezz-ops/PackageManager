#include "../headers/list.hpp"
#include <iostream>
#include <string.h>
#include <cstdio>
#include <memory>
#include <array>
#include <iomanip>

void listInstalledImages() {
    FILE* pipe = popen("docker images", "r");
    if (!pipe) {
        std::cerr << "Error opening pipe for command." << std::endl;
        return;
    }

    constexpr size_t BUFFER_SIZE = 128;
    std::array<char, BUFFER_SIZE> buffer;

    while (fgets(buffer.data(), BUFFER_SIZE, pipe) != nullptr) {
        if (strstr(buffer.data(), "REPOSITORY") != nullptr) {
            break;
        }
    }

    std::cout << "List of Installed Docker Images:\n";
    std::cout << std::setw(20) << std::left << "REPOSITORY" << std::setw(20) << "TAG" << std::setw(20) << "IMAGE ID" << '\n';
    std::cout << "------------------------------------------------------\n";

    while (fgets(buffer.data(), BUFFER_SIZE, pipe) != nullptr) {
        char repository[128], tag[128], imageID[128];
        int fieldsRead = sscanf(buffer.data(), "%s %s %s", repository, tag, imageID);

        if (fieldsRead >= 3) {
            std::cout << std::setw(20) << std::left << repository << std::setw(20) << tag << std::setw(20) << imageID << '\n';
        }
    }

    pclose(pipe);
}
