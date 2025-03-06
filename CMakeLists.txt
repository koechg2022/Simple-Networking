



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















































# Unix: cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Windows: cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#           mingw32-make .

# cmake_minimum_required(VERSION 3.10)
# project(NetworkingProject CXX)

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Set the output directory for the executable
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/objects)

# # Include directories
# include_directories(
#     ${CMAKE_SOURCE_DIR}/headers
#     ${CMAKE_SOURCE_DIR}/libs
# )

# # Add source files
# set(SOURCES
#     tests/test_server.c++
#     libs/networking.c++
#     libs/string_functions.c++
#     libs/misc_functions.c++
# )

# # Create the executable
# add_executable(test_server ${SOURCES})

# # Platform-specific configurations
# if(WIN32)
#     include_directories("C:/Program Files/OpenSSL-Win64/include")
#     target_link_libraries(test_server
#         "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libssl.lib"
#         "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libcrypto.lib"
#         ws2_32
#         iphlpapi
#     )
# else()
#     find_package(OpenSSL REQUIRED)
#     target_link_libraries(test_server OpenSSL::SSL OpenSSL::Crypto)
# endif()

# # Add compiler flags
# target_compile_options(test_server PRIVATE -Wall -Wextra)






















































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
    # Use find_package for OpenSSL on Windows as well
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")  # Optional: Specify OpenSSL installation path if needed
    find_package(OpenSSL REQUIRED)
    target_link_libraries(test_server OpenSSL::SSL OpenSSL::Crypto ws2_32 iphlpapi)
else()
    find_package(OpenSSL REQUIRED)
    target_link_libraries(test_server OpenSSL::SSL OpenSSL::Crypto)
endif()

# Add compiler flags
target_compile_options(test_server PRIVATE -Wall -Wextra)
