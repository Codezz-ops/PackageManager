cmake_minimum_required(VERSION 3.15)

project(whalec)

set(CMAKE_CXX_STANDARD 20)

set(WHALEC_HEADER_FILES
    src/headers/cmd/list.h
    src/headers/cmd/search.h
    src/headers/cmd/version.h

    src/headers/utils/install.h
    src/headers/utils/uninstall.h

    src/lib/colors.h
)

set(WHALEC_SOURCE_FILES
    src/cmd/list.c
    src/cmd/search.c
    src/cmd/version.c

    src/utils/install.c
    src/utils/uninstall.c

    src/main.c
)

add_executable(whalec ${WHALEC_HEADER_FILES} ${WHALEC_SOURCE_FILES})

# Link against libcurl
target_link_libraries(whalec PRIVATE -lcurl)
