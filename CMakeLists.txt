cmake_minimum_required(VERSION 3.15)

project(whalec)

set(CMAKE_CXX_STANDARD 20)

set(WHALEC_HEADER_FILES
    src/headers/install.h
    src/headers/search.h
    src/headers/uninstall.h
    src/headers/version.h
    src/headers/list.h
)

set(WHALEC_SOURCE_FILES
    src/main.c
    src/cmd/install.c
    src/cmd/search.c
    src/cmd/uninstall.c
    src/cmd/version.c
    src/cmd/list.c
)

add_executable(whalec ${WHALEC_HEADER_FILES} ${WHALEC_SOURCE_FILES})

# Link against libcurl
target_link_libraries(whalec PRIVATE -lcurl)
