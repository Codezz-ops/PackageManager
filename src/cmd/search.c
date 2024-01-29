#include "../headers/cmd/search.h"
#include "../lib/colors.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    fprintf(stderr, LIGHT_RED "Memory allocation error" RESET "\n");
    exit(1);
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

void printDockerInfo(const char *jsonResponse) {
  const char *repoNameStart = "\"repo_name\":\"";
  const char *descriptionStart = "\"short_description\":\"";
  const char *starsStart = "\"star_count\":";
  const char *pullsStart = "\"pull_count\":";
  const char *currentPos = jsonResponse;

  while ((currentPos = strstr(currentPos, repoNameStart)) != NULL) {
    currentPos += strlen(repoNameStart);

    const char *repoNameEnd = strchr(currentPos, '\"');
    if (!repoNameEnd) break;

    char repoName[256];
    strncpy(repoName, currentPos, repoNameEnd - currentPos);
    repoName[256 - 1] = '\0';

    currentPos = strstr(currentPos, descriptionStart);
    if (!currentPos) break;

    currentPos += strlen(descriptionStart);
    const char *descriptionEnd = strchr(currentPos, '\"');
    if (!descriptionEnd) break;

    char description[256];
    strncpy(description, currentPos, descriptionEnd - currentPos);
    description[256 - 1] = '\0';

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

void searchDockerImage(const char* imageName) {
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

    char searchUrl[256];
    snprintf(searchUrl, sizeof(searchUrl), "https://hub.docker.com/v2/search/repositories/?query=%s", imageName);

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
