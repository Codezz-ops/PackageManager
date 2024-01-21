#include <stdio.h>
#include <string.h>
#include "headers/version.h"
#include "headers/search.h"
#include "headers/install.h"
#include "headers/uninstall.h"

void printUsage(const char *programName) {
    printf("Usage: %s [options]\n", programName);
}

void printHelp() {
    printf("WhaleC - Docker Container Management\n\n");
    printf("Options:\n");
    printf("  --version         Display the program version\n");
    printf("  search <term>     Search for Docker images\n");
    printf("  install <image> <tag>   Install a Docker container\n");
    printf("  uninstall <image> <tag> Remove a Docker container\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    const char *option = argv[1];

    if (strcmp(option, "--version") == 0) {
        printf("%s", getWhaleCVersion());
    } else if (strcmp(option, "--help") == 0) {
        printHelp();
    } else if (strcmp(option, "search") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Search term is missing.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *searchTerm = argv[2];
        searchDockerImage(searchTerm);
    } else if (strcmp(option, "install") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: Image name and tag are required for installation.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *imageName = argv[2];
        const char *imageTag = argv[3];
        installDockerContainer(imageName, imageTag);
    } else if (strcmp(option, "uninstall") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: Image name and tag are required for installation.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *imageName = argv[2];
        const char *imageTag = argv[3];
        uninstallDockerContainer(imageName, imageTag);
    } else {
        fprintf(stderr, "Error: Unknown option '%s'\n", option);
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}