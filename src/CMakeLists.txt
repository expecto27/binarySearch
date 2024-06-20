include_directories(include)

set(
    SOURCE_FILES
        CsvReader.cpp
        DataStore.cpp
        Models.cpp
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
)

file(GLOB CSV_FILES "${PROJECT_SOURCE_DIR}/data/*.csv")
foreach(CSV_FILE ${CSV_FILES})
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CSV_FILE} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
endforeach()
