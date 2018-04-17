function (configure_target_executable target_name src)
    add_executable (${target_name} ${src})
    target_link_libraries (${target_name} PRIVATE cpprestsdk::cpprest)
endfunction ()

cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
set (PROJECT_NAME vehicle-router-server)
project (${PROJECT_NAME})

find_package (cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

set (SRC "src")
set (SOURCES ${SRC}/main.cpp)

configure_target_executable (${PROJECT_NAME} "${SOURCES}")