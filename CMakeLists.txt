cmake_minimum_required(VERSION 3.0.0)
project(run VERSION 0.1.0)
add_definitions(-std=c++11)

include(CTest)
enable_testing()


include_directories("${CMAKE_SOURCE_DIR}/include")
add_subdirectory(src)
add_executable(run run.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(run Functions)
