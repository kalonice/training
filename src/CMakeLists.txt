set(target code_lib)

file(GLOB_RECURSE CPPS *.cpp)
file(GLOB_RECURSE HPPS ../include/*.h ../include/*.hpp)

include_directories(../include)

add_style_check_target(TARGET ${target}_lint
                       SOURCES ${CPPS} ${HPPS})
add_library(${target} ${CPPS} ${HPPS})
