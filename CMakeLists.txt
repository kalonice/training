cmake_minimum_required(VERSION 3.2)

project(arithmometer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

include_directories(include)
add_subdirectory(3rdparty)
add_subdirectory(app)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wpedantic -Wextra -Werror -Wconversion)
endif()

include(CppLint)

add_subdirectory(src)
add_subdirectory(test)
