



# cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON




# cmake_minimum_required(VERSION 3.30)
# project(Personal_Website CXX)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # Add this line to recognize .h++ as a C++ header file
# set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS cpp cxx cc c++ h hpp hxx h++)

# # Set the OpenSSL root directory
# set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@3)

# # Find OpenSSL package
# find_package(OpenSSL REQUIRED)

# # Set the output directory for object files and executables
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../objects)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../objects)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../objects)

# # Create a library from the files in the libs directory
# file(GLOB LIB_SOURCES "libs/*.c++")
# add_library(project_lib STATIC ${LIB_SOURCES})
# target_include_directories(project_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs ${OPENSSL_INCLUDE_DIR})

# # Add your source files here
# add_executable(test_server tests/test_server.c++)

# # Add compiler flags
# target_compile_options(test_server PRIVATE -Wall -Wextra)

# # If you have additional include directories, add them like this:
# target_include_directories(test_server PRIVATE headers libs ${OPENSSL_INCLUDE_DIR})

# # Link the project_lib and OpenSSL to test_server
# target_link_libraries(test_server PRIVATE project_lib ${OPENSSL_LIBRARIES})

# # For wxWidgets and IntelliSense support
# # find_package(wxWidgets COMPONENTS core base REQUIRED)
# # include(${wxWidgets_USE_FILE})
# # target_link_libraries(test_server PRIVATE ${wxWidgets_LIBRARIES})
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)






































# cmake_minimum_required(VERSION 3.10)

# project(networking)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # Enable compile commands export
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # Find OpenSSL
# find_package(OpenSSL REQUIRED)

# # Include directories
# include_directories(${PROJECT_SOURCE_DIR}/headers)
# include_directories(${PROJECT_SOURCE_DIR}/libs)
# include_directories(${OPENSSL_INCLUDE_DIR})

# # Create output directories
# file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# # Add source files
# set(SOURCES
#     ${PROJECT_SOURCE_DIR}/libs/networking_defs.c++
#     ${PROJECT_SOURCE_DIR}/libs/string_functions_defs.c++
#     ${PROJECT_SOURCE_DIR}/libs/misc_functions.c++
# )

# # Create static libraries from source files
# add_library(networking_functions STATIC ${PROJECT_SOURCE_DIR}/libs/networking_defs.c++)
# add_library(string_functions STATIC ${PROJECT_SOURCE_DIR}/libs/string_functions_defs.c++)
# add_library(misc_functions STATIC ${PROJECT_SOURCE_DIR}/libs/misc_functions.c++)

# # Create executables
# add_executable(string_tests ${PROJECT_SOURCE_DIR}/tests/test_server.c++)

# # Link libraries to executables
# target_link_libraries(string_tests PRIVATE networking_functions string_functions misc_functions ${OPENSSL_LIBRARIES})

# # Windows-specific libraries
# if(WIN32)
#     target_link_libraries(string_tests PRIVATE ws2_32)
# endif()

# # Set output directory for the executables
# set_target_properties(string_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/objects)

# # Add compiler warning flags
# if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
#     target_compile_options(networking_functions PRIVATE -Wall -Wextra)
#     target_compile_options(string_functions PRIVATE -Wall -Wextra)
#     target_compile_options(misc_functions PRIVATE -Wall -Wextra)
# elseif(MSVC)
#     target_compile_options(networking_functions PRIVATE /W4)
#     target_compile_options(string_functions PRIVATE /W4)
#     target_compile_options(misc_functions PRIVATE /W4)
# endif()

# # Ensure .c++ extension is recognized
# if(MSVC)
#     set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)
# endif()



















































# Unix: cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Windows: cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#           cmake --build .

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
    libs/networking_defs.c++
    libs/string_functions_defs.c++
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
target_compile_options(test_server PRIVATE -Wall)
