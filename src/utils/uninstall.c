#include "../headers/utils/uninstall.h"
#include "../lib/colors.h"
#include <stdio.h>
#include <stdlib.h>

void uninstallDockerContainer(const char *imageName, const char *imageTag) {
    const char *tag = (imageTag != NULL) ? imageTag : "latest";

    char dockerCommand[256];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker rmi %s:%s", imageName, tag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf(LIGHT_BLUE "Docker container %s:(%s) successfully uninstalled" RESET "\n", imageName, tag);
    } else {
        fprintf(stderr, LIGHT_RED "Error uninstalling Docker container %s:%s." RESET "\n", imageName, tag);
    }
}