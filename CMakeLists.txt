



cmake_minimum_required(VERSION 3.10)

project(networking)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/headers)
include_directories(${PROJECT_SOURCE_DIR}/prototypes)

# Create output directories
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# Add source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/source/networking_functions.c++
    ${PROJECT_SOURCE_DIR}/source/string_functions.c++
)

# Create static libraries from source files
add_library(networking_functions STATIC ${PROJECT_SOURCE_DIR}/source/networking_functions.c++)
add_library(string_functions STATIC ${PROJECT_SOURCE_DIR}/source/string_functions.c++)

# Create executables
add_executable(string_tests ${PROJECT_SOURCE_DIR}/tests/string_tests.c++)
add_executable(network_tests ${PROJECT_SOURCE_DIR}/tests/network_tests.c++)

# Link libraries to executables
target_link_libraries(string_tests PRIVATE networking_functions string_functions)
target_link_libraries(network_tests PRIVATE networking_functions string_functions)

# Set output directory for the executables
set_target_properties(string_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)
set_target_properties(network_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# Add compiler warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(string_functions PRIVATE -Wall -Wextra)
    target_compile_options(networking_functions PRIVATE -Wall -Wextra)
elseif(MSVC)
    target_compile_options(string_functions PRIVATE /W4)
    target_compile_options(networking_functions PRIVATE /W4)
endif()