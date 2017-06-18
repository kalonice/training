include(CMakeParseArguments)
find_package(PythonInterp)

set(LINTING_APP ${CMAKE_SOURCE_DIR}/3rdparty/cpplint.py)
file(GLOB LINT_CONFIG ${CMAKE_SOURCE_DIR}/CPPLINT.cfg)

function(add_style_check_target)
    if(NOT PYTHONINTERP_FOUND)
        message(WARNING "Skip linting, python not found")
        return()
    endif()

    cmake_parse_arguments(LINT "" TARGET "SOURCES" ${ARGN})
    if(NOT LINT_TARGET)
        message(FATAL_ERROR "You must provide a target name")
    endif(NOT LINT_TARGET)

    list(REMOVE_DUPLICATES LINT_SOURCES)
    list(SORT LINT_SOURCES)

    add_custom_target(${LINT_TARGET} ALL
            COMMAND "${CMAKE_COMMAND}" -E chdir
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${PYTHON_EXECUTABLE}"
            ${LINTING_APP} ${LINT_SOURCES}
            DEPENDS ${LINT_SOURCES}
            COMMENT "Linting ${LINT_TARGET}"
            VERBATIM
            SOURCES ${LINTING_APP} ${LINT_CONFIG})
endfunction()