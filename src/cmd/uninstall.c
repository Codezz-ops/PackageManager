#include "../headers/uninstall.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LEN 256

void uninstallDockerContainer(const char *imageName, const char *imageTag) {
    char dockerCommand[256];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker rmi %s:%s", imageName, imageTag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf("Docker container successfully removed.\n");
    } else {
        fprintf(stderr, "Error removing Docker container.\n");
    }
}