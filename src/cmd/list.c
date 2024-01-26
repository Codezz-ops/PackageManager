#include "../headers/cmd/list.h"
#include <stdio.h>
#include <string.h>

void listInstalledImages(void) {
    FILE *pipe = popen("docker images", "r");
    if (!pipe) {
        fprintf(stderr, "Error opening pip for command.\n");
        return;
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (strstr(buffer, "REPOSITORY") != NULL) {
            break;
        }
    }

    printf("List of Installed Docker Images:\n");
    printf("%-20s %-20s %-20s\n", "REPOSITORY", "TAG", "IMAGE ID");
    printf("------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        char repository[128], tag[128], imageID[128];
        int fieldsRead = sscanf(buffer, "%s %s %s", repository, tag, imageID);

        if (fieldsRead >= 3) {
            printf("%-20s %-20s %-20s\n", repository, tag, imageID);
        }
    }

    pclose(pipe);
}