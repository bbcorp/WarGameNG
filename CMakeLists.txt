# We want recent cmake version
cmake_minimum_required(VERSION 3.0)

project(WarGameNG)
# The version number
set (Server_VERSION_MAJOR 0)
set (Server_VERSION_MINOR 1)
add_subdirectory(Client)
add_subdirectory(Server)