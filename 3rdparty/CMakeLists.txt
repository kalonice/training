

add_subdirectory(tbb)

file(GLOB GTEST_CPPS "gtest/googletest/src/gtest-all.cc")
file(GLOB_RECURSE GTEST_HPPS "gtest/googletest/include/*.h")

include_directories(./gtest/googletest/include)
include_directories(./gtest/googletest/)

if(MSVC)
    #vc 2012 fix for vararg templates
    ADD_DEFINITIONS (/D_VARIADIC_MAX=10)
    MESSAGE(STATUS "MSVC: Set variadic max to 10 for MSVC compatibility")
endif()

add_library(gtest ${GTEST_CPPS} ${GTEST_HPPS})

