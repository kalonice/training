set(target task_arithmometer)

file(GLOB CPPS *.cpp)
file(GLOB HPPS *.hpp)

include_directories(../3rdparty/tbb/include)

add_executable(${target} ${CPPS} ${HPPS})
target_link_libraries(${target} PRIVATE tbb)
set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)
