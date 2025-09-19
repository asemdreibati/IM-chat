cmake_minimum_required(VERSION 3.31.5)

project(IMChat LANGUAGES CXX)

# Set the QT_DIR environment variable to your Qt installation path
set(CMAKE_PREFIX_PATH   $ENV{QT_DIR} )

add_subdirectory(Client-Side)
add_subdirectory(Server-Side)
