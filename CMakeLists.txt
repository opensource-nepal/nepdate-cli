cmake_minimum_required(VERSION 3.10)

project(nepdate-cli VERSION 2.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(nepdate-cli src/main.cpp)

# Allow user to override this on cmake command line
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX /usr/local CACHE PATH "Install path prefix")
endif()

install(TARGETS nepdate-cli
    RUNTIME DESTINATION bin
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

add_custom_target(run
    COMMAND $<TARGET_FILE:nepdate-cli>
    DEPENDS nepdate-cli
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

