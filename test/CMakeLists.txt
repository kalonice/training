set(target tests)

file(GLOB CPPS *.cpp)
file(GLOB HPPS ../include/*.h ../include/*.hpp)

find_package(Threads)

include_directories(../3rdparty/gtest/googletest/include)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if(MSVC)
    #vc 2012 fix for vararg templates
    ADD_DEFINITIONS (/D_VARIADIC_MAX=10)
    MESSAGE(STATUS "MSVC: Set variadic max to 10 for MSVC compatibility")
endif()

add_style_check_target(TARGET ${target}_lint
                       SOURCES ${CPPS} ${HPPS})
add_executable(${target} ${CPPS} ${HPPS})
target_link_libraries(${target} gtest code_lib ${CMAKE_THREAD_LIBS_INIT})
