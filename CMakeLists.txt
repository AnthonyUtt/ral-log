# Setting CMake required version
cmake_minimum_required(VERSION 3.0)

# Initializing project info
set(PROJECT_VERSION "1.0")
project(ral-log VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# Source file info
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SOURCES ${SRC_DIR}/log/*.cpp)

# Creating library target
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Naming convention for output files
set_target_properties(${PROJECT_NAME}
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)

# Compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # g++
    target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra)
    # Setting definition to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE GNU_EXPORT)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
    # Setting definition to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()
