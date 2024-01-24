#include "../headers/search.hpp"
#include <string.h>
#include <string>
#include <iostream>
#include <memory>
#include <curl/curl.h>

#define MAX_URL_LEN 256

struct MemoryStruct {
    char* memory;
    size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    auto* mem = static_cast<MemoryStruct*>(userp);

    mem->memory = static_cast<char*>(std::realloc(mem->memory, mem->size + realsize + 1));
    if (mem->memory == nullptr) {
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void cleanupMemory(std::unique_ptr<MemoryStruct>& chunk) {
    std::free(chunk->memory);
    chunk->memory = nullptr;
    chunk->size = 0;
}

void printDockerInfo(const char* jsonResponse) {
    const char* repoNameStart = "\"repo_name\":\"";
    const char* descriptionStart = "\"short_description\":\"";
    const char* starsStart = "\"star_count\":";
    const char* pullsStart = "\"pull_count\":";

    const char* currentPos = jsonResponse;
    while ((currentPos = strstr(currentPos, repoNameStart)) != nullptr) {
        currentPos += strlen(repoNameStart);
        const char* repoNameEnd = strchr(currentPos, '\"');
        if (!repoNameEnd) break;

        std::string repoName(currentPos, repoNameEnd - currentPos);

        currentPos = strstr(currentPos, descriptionStart);
        if (!currentPos) break;
        currentPos += strlen(descriptionStart);
        const char* descriptionEnd = strchr(currentPos, '\"');
        if (!descriptionEnd) break;

        std::string description(currentPos, descriptionEnd - currentPos);

        currentPos = strstr(currentPos, starsStart);
        if (!currentPos) break;
        currentPos += strlen(starsStart);
        long long stars = strtoll(currentPos, nullptr, 10);

        currentPos = strstr(currentPos, pullsStart);
        if (!currentPos) break;
        currentPos += strlen(pullsStart);
        long long pulls = strtoll(currentPos, nullptr, 10);

        std::cout << "Repo Name: " << repoName << '\n'
                  << "Description: " << description << '\n'
                  << "Stars: " << stars << '\n'
                  << "Pulls: " << pulls << '\n'
                  << '\n';
    }
}

void searchDockerImage(const char* image) {
    CURL* curl;
    CURLcode res;
    auto chunk = std::make_unique<MemoryStruct>();

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        chunk->memory = static_cast<char*>(std::malloc(1));
        chunk->size = 0;

        char searchUrl[MAX_URL_LEN];
        snprintf(searchUrl, sizeof(searchUrl), "https://hub.docker.com/v2/search/repositories/?query=%s", image);

        curl_easy_setopt(curl, CURLOPT_URL, searchUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(chunk.get()));

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printDockerInfo(chunk->memory);
            cleanupMemory(chunk);

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
