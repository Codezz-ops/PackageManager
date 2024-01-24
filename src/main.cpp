#include <iostream>
#include <cstring>
#include "headers/list.hpp"
#include "headers/version.hpp"
#include "headers/search.hpp"
#include "headers/install.hpp"
#include "headers/uninstall.hpp"

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options]\n";
}

void printHelp() {
    std::cout << "WhaleC - Docker Container Management\n\n";
    std::cout << "Options:\n";
    std::cout << "  --version         Display the program version\n";
    std::cout << "  list              List all installed Docker container\n";
    std::cout << "  search <term>     Search for Docker images\n";
    std::cout << "  install <image> <tag>   Install a Docker container\n";
    std::cout << "  uninstall <image> <tag> Remove a Docker container\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    const char* option = argv[1];

    if (std::strcmp(option, "--version") == 0) {
        std::cout << getWhaleCVersion();
    } else if (std::strcmp(option, "--help") == 0) {
        printHelp();
    } else if (std::strcmp(option, "list") == 0) {
        listInstalledImages();
    } else if (std::strcmp(option, "search") == 0) {
        if (argc < 3) {
            std::cerr << "Error: Search term is missing.\n";
            printUsage(argv[0]);
            return 1;
        }
        const char* searchTerm = argv[2];
        searchDockerImage(searchTerm);
    } else if (std::strcmp(option, "install") == 0) {
        if (argc < 3) {
            std::cerr << "Error: Image name and tag are required for installation.\n";
            printUsage(argv[0]);
            return 1;
        }
        const char* imageName = argv[2];
        const char* imageTag = (argc >= 4) ? argv[3] : nullptr;
        installDockerContainer(imageName, imageTag);
    } else if (std::strcmp(option, "uninstall") == 0) {
        if (argc < 3) {
            std::cerr << "Error: Image name and tag are required for uninstallation.\n";
            printUsage(argv[0]);
            return 1;
        }
        const char* imageName = argv[2];
        const char* imageTag = (argc >= 4) ? argv[3] : nullptr;
        uninstallDockerContainer(imageName, imageTag);
    } else {
        std::cerr << "Error: Unknown option '" << option << "'\n";
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}
