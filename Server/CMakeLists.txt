# We want recent cmake version
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)
enable_language(CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})
set(CMAKE_GENERATOR_PLATFORM x64)

project(Server)
# The version number
set(Server_VERSION_MAJOR 0)
set(Server_VERSION_MINOR 1)

add_definitions(-DASIO_STANDALONE
-DWINVER=0x0601
-D_WIN32_WINNT=0x0601)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/lib/${CMAKE_GENERATOR_PLATFORM})

file(GLOB SRCS src/*.cpp)

add_executable(Server ${SRCS})

target_link_libraries(Server sfml-system pthread)