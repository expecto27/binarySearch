cmake_minimum_required(VERSION 3.10)

project(SvyazcomProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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