#include "../headers/uninstall.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

#define MAX_COMMAND_LEN 256

void uninstallDockerContainer(const char *imageName, const char *imageTag) {
    const char *tag = (imageTag != nullptr) ? imageTag : "latest";

    char dockerCommand[MAX_COMMAND_LEN];
    std::snprintf(dockerCommand, sizeof(dockerCommand), "docker rmi %s:%s", imageName, tag);

    int result = std::system(dockerCommand);

    if (result == 0) {
        std::cout << "Docker container " << imageName << ':' << tag << " successfully uninstalled" << std::endl;
    } else {
        std::cerr << "Error uninstalling Docker container " << imageName << ':' << tag << '.' << std::endl;
    }
}
