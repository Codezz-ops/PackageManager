#include "../headers/install.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 256

void installDockerContainer(const char *image, const char *imagetag) {
    const char *tag = (imagetag != NULL) ? imagetag : "latest";

    char dockerCommand[MAX_COMMAND_LEN];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker pull %s:%s", image, tag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf("Docker container %s:%s successfully installed\n", image, tag);
    } else {
        fprintf(stderr, "Error installing Docker container %s:%s.\n", image, tag);
    }
}
