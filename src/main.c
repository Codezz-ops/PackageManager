#include <stdio.h>
#include <string.h>
#include "headers/cmd/list.h"
#include "headers/cmd/search.h"
#include "headers/cmd/version.h"
#include "headers/utils/install.h"
#include "headers/utils/uninstall.h"

void printUsage(const char *programName) {
    printf("Usage: %s [options]\n", programName);
}

void printHelp() {
    printf("WhaleC - Docker Container Management\n\n");
    printf("Options:\n");
    printf("  --version         Display the program version\n");
    printf("  list              List all installed Docker container\n");
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
    } else if (strcmp(option, "list") == 0) {
        listInstalledImages();
    } else if (strcmp(option, "search") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Search term is missing.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *searchTerm = argv[2];
        searchDockerImage(searchTerm);
    } else if (strcmp(option, "install") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Image name and tag are required for installation.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *imageName = argv[2];
        const char *imageTag = (argc >= 4) ? argv[3] : NULL;
        installDockerContainer(imageName, imageTag);
    } else if (strcmp(option, "uninstall") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Image name and tag are required for installation.\n");
            printUsage(argv[0]);
            return 1;
        }
        const char *imageName = argv[2];
        const char *imageTag = (argc >= 4) ? argv[3] : NULL;
        uninstallDockerContainer(imageName, imageTag);
    } else {
        fprintf(stderr, "Error: Unknown option '%s'\n", option);
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}