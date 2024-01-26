#include "../headers/utils/install.h"
#include "../lib/colors.h"
#include <stdio.h>

void installDockerContainer(const char* imageName, const char* imageTag) {
    const char* tag = (imageTag != NULL) ? imageTag : "latest";

    char dockerCommand[256];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker pull %s:%s > /dev/null 2>&1", imageName, tag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf(LIGHT_BLUE "Docker container %s:%s successfully installed" RESET "\n", imageName, tag);
    } else {
        fprintf(stderr, LIGHT_RED "Error installing Docker container %s:%s." RESET "\n", imageName, tag);
    }
}