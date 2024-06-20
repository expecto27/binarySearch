include_directories(include)

set(
    SOURCE_FILES
        DataStore.cpp
        Models.cpp
)

add_library(
    csvreader-lib
        CsvReader.cpp
)

target_link_libraries(
    csvreader-lib
        lazycsv::lazycsv
        fmt::fmt
)


add_library(
    ${CMAKE_PROJECT_NAME}-lib
        ${SOURCE_FILES}
)

add_executable(
    ${CMAKE_PROJECT_NAME}
        main.cpp
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
        ${CMAKE_PROJECT_NAME}-lib
        ${REQUIRED_LIBRARIES}
        csvreader-lib
)

install(
    TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
    