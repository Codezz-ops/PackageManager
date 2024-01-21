#include "../headers/uninstall.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMMAND_LEN 256

void uninstallDockerContainer(const char *imageName, const char *imageTag) {
    const char *tag = (imageTag != NULL) ? imageTag : "latest";

    char dockerCommand[MAX_COMMAND_LEN];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker rmi %s:%s", imageName, tag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf("Docker container %s:%s successfully uninstalled\n", imageName, tag);
    } else {
        fprintf(stderr, "Error uninstalling Docker container %s:%s.\n", imageName, tag);
    }
}