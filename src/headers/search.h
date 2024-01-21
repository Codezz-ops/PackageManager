#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
void searchDockerImage(const char *osName);

#endif // SEARCH_H