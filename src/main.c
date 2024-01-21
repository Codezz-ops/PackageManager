#include <stdio.h>
#include <string.h>
#include "headers/version.h"
#include "headers/search.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [options]", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf(getWhaleCVersion());
    } else if (strcmp(argv[1], "search") == 0) {
        const char *search = argv[2];
        searchDockerImage(search);
    }

    return 0;
}