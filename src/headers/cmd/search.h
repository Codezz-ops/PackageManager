#pragma once

#include <stdlib.h>

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
void searchDockerImage(const char* imageName);
void printDockerInfo(const char *jsonResponse);