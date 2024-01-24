#include "../headers/install.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>

#define MAX_COMMAND_LEN 256

void handleDockerOutput(const char* line) {
    char* hash = std::strtok(const_cast<char*>(line), ":");
    char* status = std::strtok(NULL, "\n");

    if (hash && status) {
        std::cout << "\033[K";
        std::cout << "\rstatus: {" << hash << ": " << status << "}";
        std::cout.flush();
    }
}

void installDockerContainer(const char* image, const char* imagetag) {
    const char* tag = (imagetag != nullptr) ? imagetag : "latest";

    char dockerCommand[MAX_COMMAND_LEN];
    std::snprintf(dockerCommand, sizeof(dockerCommand), "docker pull %s:%s", image, tag);

    FILE* pipe = popen(dockerCommand, "r");
    if (!pipe) {
        perror("popen failed!");
        return;
    }

    char line[MAX_COMMAND_LEN];
    while (fgets(line, sizeof(line), pipe)) {
        handleDockerOutput(line);
    }

    int result = pclose(pipe);

    if (result == 0) {
        std::cout << "Docker container " << image << ':' << tag << " successfully installed" << std::endl;
    } else {
        std::cerr << "Error installing Docker container " << image << ':' << tag << '.' << std::endl;
    }
}
