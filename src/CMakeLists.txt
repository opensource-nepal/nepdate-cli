cmake_minimum_required(VERSION 3.5)
project(nepdate-cli VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(nepdate-cli main.cpp)

set(CMAKE_INSTALL_PREFIX /usr/local)

# Install the executable (adjust the path if necessary)
install(TARGETS nepdate-cli)
