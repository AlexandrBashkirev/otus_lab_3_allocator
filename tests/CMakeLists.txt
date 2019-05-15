project(${PROJECT_NAME}_tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

list(APPEND ${PROJECT_NAME}_SOURCES
    list_test.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src
)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})