#include "../headers/utils/install.h"
#include "../lib/colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_LENGTH 12

void printProgressBar(int progress) {
    const int barWidth = 50;
    int pos = barWidth * progress / 100;

    printf("[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%%\r", progress);
    fflush(stdout);
}

void installDockerContainer(const char* imageName, const char* imageTag) {
    const char* tag = (imageTag != NULL) ? imageTag : "latest";

    char dockerCommand[256];
    snprintf(dockerCommand, sizeof(dockerCommand), "docker pull %s:%s", imageName, tag);

    FILE* fp = popen(dockerCommand, "r");

    if (fp == NULL) {
        fprintf(stderr, LIGHT_RED "Error executing Docker pull command." RESET "\n");
        return;
    }

    char buffer[1024];
    int totalHashes = 0;
    int currentHashes = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "Downloading") != NULL || strstr(buffer, "Waiting") != NULL) {
            totalHashes++;
            char* spacePos = strchr(buffer, ' ');
            if (spacePos != NULL) {
                *spacePos = '\0';
                printf("%s", buffer);
                currentHashes++;

                int progress = (currentHashes * 100) / totalHashes;
                printProgressBar(progress);
                printf("\n");
            }
        }
    }

    int result = pclose(fp);

    if (result == 0) {
        printf(LIGHT_BLUE "Docker container %s:(%s) successfully installed" RESET "\n", imageName, tag);
    } else {
        fprintf(stderr, LIGHT_RED "Error installing Docker container %s:(%s)." RESET "\n", imageName, tag);
    }
}
