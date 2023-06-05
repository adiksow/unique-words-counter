cmake_minimum_required(VERSION 3.16)
project(uwc LANGUAGES CXX)

# Set C++ standard/compile-time options                       
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB COMMON_SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${COMMON_SRC})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
