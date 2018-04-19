function (configure_target_executable target_name src)
    add_executable (${target_name} ${src})
    target_link_libraries (${target_name} PRIVATE cpprestsdk::cpprest)
endfunction ()

cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
set (PROJECT_NAME vehicle-router-server)
project (${PROJECT_NAME})

find_package (cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

set (SRC src)
set (CONTROLLERS controller)
set (SOURCES ${SRC}/service_runner.cpp
             ${SRC}/${CONTROLLERS}/handler.h
             ${SRC}/${CONTROLLERS}/controller.h
             ${SRC}/${CONTROLLERS}/controller.cpp)

configure_target_executable (${PROJECT_NAME} "${SOURCES}")