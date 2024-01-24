cmake_minimum_required(VERSION 3.15)

project(whalec)

set(CMAKE_CXX_STANDARD 20)

set(WHALEC_HEADER_FILES
    src/headers/install.hpp
    src/headers/search.hpp
    src/headers/uninstall.hpp
    src/headers/version.hpp
    src/headers/list.hpp
)

set(WHALEC_SOURCE_FILES
    src/main.cpp
    src/cmd/install.cpp
    src/cmd/search.cpp
    src/cmd/uninstall.cpp
    src/cmd/version.cpp
    src/cmd/list.cpp
)

add_executable(whalec ${WHALEC_HEADER_FILES} ${WHALEC_SOURCE_FILES})

# Link against libcurl
target_link_libraries(whalec PRIVATE -lcurl)
