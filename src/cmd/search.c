#include "../headers/search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_REPO_NAME_LEN 256
#define MAX_DESCRIPTION_LEN 256
#define MAX_URL_LEN 256
#define MAX_RESPONSE_LEN 4096

#define REPO_NAME_KEY "repo_name"
#define DESCRIPTION_KEY "short_description"
#define STARS_KEY "star_count"
#define PULLS_KEY "pull_count"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void cleanupMemory(struct MemoryStruct *chunk) {
    free(chunk->memory);
    chunk->memory = NULL;
    chunk->size = 0;
}

static void printDockerInfo(const char *jsonResponse) {
    const char *repoNameStart = "\"" REPO_NAME_KEY "\":\"";
    const char *descriptionStart = "\"" DESCRIPTION_KEY "\":\"";
    const char *starsStart = "\"" STARS_KEY "\":";
    const char *pullsStart = "\"" PULLS_KEY "\":";

    const char *currentPos = jsonResponse;
    while ((currentPos = strstr(currentPos, repoNameStart)) != NULL) {
        currentPos += strlen(repoNameStart);
        const char *repoNameEnd = strchr(currentPos, '\"');
        if (!repoNameEnd) break;

        char repoName[MAX_REPO_NAME_LEN];
        strncpy(repoName, currentPos, repoNameEnd - currentPos);
        repoName[MAX_REPO_NAME_LEN - 1] = '\0';

        currentPos = strstr(currentPos, descriptionStart);
        if (!currentPos) break;
        currentPos += strlen(descriptionStart);
        const char *descriptionEnd = strchr(currentPos, '\"');
        if (!descriptionEnd) break;

        char description[MAX_DESCRIPTION_LEN];
        strncpy(description, currentPos, descriptionEnd - currentPos);
        description[MAX_DESCRIPTION_LEN - 1] = '\0';

        currentPos = strstr(currentPos, starsStart);
        if (!currentPos) break;
        currentPos += strlen(starsStart);
        long long stars = strtoll(currentPos, NULL, 10);

        currentPos = strstr(currentPos, pullsStart);
        if (!currentPos) break;
        currentPos += strlen(pullsStart);
        long long pulls = strtoll(currentPos, NULL, 10);

        printf("Repo Name: %s\n", repoName);
        printf("Description: %s\n", description);
        printf("Stars: %lld\n", stars);
        printf("Pulls: %lld\n", pulls);
        printf("\n");
    }
}

void searchDockerImage(const char *image) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        chunk.memory = malloc(1);
        if (chunk.memory == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return;
        }
        chunk.size = 0;

        char searchUrl[MAX_URL_LEN];
        snprintf(searchUrl, sizeof(searchUrl), "https://hub.docker.com/v2/search/repositories/?query=%s", image);

        curl_easy_setopt(curl, CURLOPT_URL, searchUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printDockerInfo(chunk.memory);

        curl_easy_cleanup(curl);
        cleanupMemory(&chunk);
    }

    curl_global_cleanup();
}