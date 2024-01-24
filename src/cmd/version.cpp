#include "../headers/version.hpp"
#include <cstdio>

const char* getWhaleCVersion() {
    static char versionString[20];

    std::sprintf(versionString, "WhaleC version: %d.%d.%d", WHALEC_MAJOR_VERSION, WHALEC_MINOR_VERSION, WHALEC_PATCH_VERSION);

    return versionString;
}
