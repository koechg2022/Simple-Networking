# Unix: cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Windows: cmake .. -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#           mingw32-make .

cmake_minimum_required(VERSION 3.16)

# Recognize custom C++ extensions
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS c++ C++ cpp cxx cc C)
set(CMAKE_CXX_HEADER_FILE_EXTENSIONS h++ H++ hpp hxx hh H h "")

project(SimpleNetworking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/objects)

# Include headers directory
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Gather library sources
file(GLOB LIB_SOURCES
    "${CMAKE_SOURCE_DIR}/libraries/*.c++"
    "${CMAKE_SOURCE_DIR}/libraries/*.cpp"
    "${CMAKE_SOURCE_DIR}/libraries/*.cc"
    "${CMAKE_SOURCE_DIR}/libraries/*.cxx"
)

# Gather test sources
file(GLOB TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/tests/*.c++"
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    "${CMAKE_SOURCE_DIR}/tests/*.cc"
    "${CMAKE_SOURCE_DIR}/tests/*.cxx"
)

# OpenSSL discovery for macOS
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/openssl@3")
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/openssl@3")
endif()

find_package(OpenSSL REQUIRED)

# Create executables for each test source
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${LIB_SOURCES} ${TEST_SRC})

    if(WIN32)
        target_link_libraries(${TEST_NAME}
            ws2_32
            crypt32
            gdi32
            iphlpapi
            OpenSSL::SSL
            OpenSSL::Crypto
        )
    else()
        target_link_libraries(${TEST_NAME}
            OpenSSL::SSL
            OpenSSL::Crypto
        )
    endif()
endforeach()
