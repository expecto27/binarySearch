cmake_minimum_required(VERSION 3.10)

project(SvyazcomProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# prohibit in-source-builds
IF (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  MESSAGE(STATUS "In-source-builds are not allowed")
  MESSAGE(STATUS "Clean your source directory (e.g. delete the CMakeCache.txt file)")
  MESSAGE(FATAL_ERROR "Please create a separate build directory and call CMake again, cmake -H. -B.build")
ENDIF (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})

# enable Werror for gcc
IF(CMAKE_COMPILER_IS_GNUCC )
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror")
ENDIF()

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK
            "--enable=all"
            "--suppressions-list=${PROJECT_SOURCE_DIR}/CppCheckSuppressions.txt"
            "--error-exitcode=1"
    )
endif()


find_package(fmt)
find_package(cxxopts)


include_directories(${PROJECT_SOURCE_DIR}/svyazcom)

set(SOURCE_FILES
    svyazcom/CsvReader.cpp
    svyazcom/DataStore.cpp
    svyazcom/Models.cpp
    svyazcom/DataParser.cpp
)

add_library(
    SvyazcomLib
        ${SOURCE_FILES}
)

add_executable(
    SvyazcomProject 
        svyazcom/main.cpp
)

target_link_libraries(
    SvyazcomProject 
        SvyazcomLib
        fmt::fmt 
        cxxopts::cxxopts
)

file(GLOB CSV_FILES "${PROJECT_SOURCE_DIR}/svyazcom/*.csv")
foreach(CSV_FILE ${CSV_FILES})
    add_custom_command(
        TARGET SvyazcomProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CSV_FILE} $<TARGET_FILE_DIR:SvyazcomProject>
    )
endforeach()