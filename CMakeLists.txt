# Unix: cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Windows: cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#           mingw32-make .

cmake_minimum_required(VERSION 3.10)
project(NetworkingProject CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/objects)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/libs
)

# Add source files
set(SOURCES
    tests/test_server.c++
    libs/networking.c++
    libs/string_functions.c++
    libs/misc_functions.c++
)

# Create the executable
add_executable(test_server ${SOURCES})

# Platform-specific configurations
if(WIN32)
    include_directories("C:/Program Files/OpenSSL-Win64/include")
    target_link_libraries(test_server
        "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libssl.lib"
        "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libcrypto.lib"
        ws2_32
        iphlpapi
    )
else()
    find_package(OpenSSL REQUIRED)
    target_link_libraries(test_server OpenSSL::SSL OpenSSL::Crypto)
endif()

# Add compiler flags
target_compile_options(test_server PRIVATE -Wall -Wextra)