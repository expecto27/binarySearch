cmake_minimum_required(VERSION 3.10)

project(SvyazcomProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/svyazcom)

set(SOURCE_FILES
    svyazcom/CsvReader.cpp
    svyazcom/DataStore.cpp
    svyazcom/Models.cpp
    svyazcom/main.cpp
)

add_library(SvyazcomLib
    svyazcom/CsvReader.cpp
    svyazcom/DataStore.cpp
    svyazcom/Models.cpp
)

add_executable(SvyazcomProject ${SOURCE_FILES})

target_link_libraries(SvyazcomProject SvyazcomLib)

file(GLOB CSV_FILES "${PROJECT_SOURCE_DIR}/svyazcom/*.csv")
foreach(CSV_FILE ${CSV_FILES})
    add_custom_command(
        TARGET SvyazcomProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CSV_FILE} $<TARGET_FILE_DIR:SvyazcomProject>
    )
endforeach()