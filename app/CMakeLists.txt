set(target task_arithmometer)

find_package( Curses REQUIRED )

file(GLOB CPPS *.cpp)
file(GLOB HPPS *.hpp)

include_directories(../3rdparty/tbb/include)

include_directories( ${CURSES_INCLUDE_DIRS} )

add_executable(${target} ${CPPS} ${HPPS})
target_link_libraries(${target}  PRIVATE code_lib tbb ${CURSES_LIBRARIES})
set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)
