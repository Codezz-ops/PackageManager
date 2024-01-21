#include "../headers/install.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 256

void installDockerContainer(const char *image, const char *tag) {
    char dockerCommand[MAX_COMMAND_LEN];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker pull %s:%s", image, tag);

    int result = system(dockerCommand);

    if (result == 0) {
        printf("Docker container %s successfully installed\n", image);
    } else {
        fprintf(stderr, "Error installing Docker container.\n");
    }
}