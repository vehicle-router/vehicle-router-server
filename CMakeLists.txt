function (configure_target_executable target_name src)
    add_executable (${target_name} ${src})
    target_include_directories (${target_name} PRIVATE "${CudaRouterLibrary_INCLUDE_DIRS}")
    target_link_libraries (${target_name} PRIVATE cpprestsdk::cpprest
            optimized "${CudaRouterLibrary_LIBRARIES}"
            debug "${CudaRouterLibrary_LIBRARIES_DEB}")
endfunction ()

cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
set (PROJECT_NAME vehicle-router-server)
project (${PROJECT_NAME})

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package (cpprestsdk REQUIRED NAMES cpprestsdk cpprest)
find_package (CudaRouterLibrary REQUIRED)

set (SRC src)
set (CONTROLLERS controller)
set (SOURCES ${SRC}/service_runner.cpp
             ${SRC}/interrupts.h
             ${SRC}/${CONTROLLERS}/handler.h
             ${SRC}/${CONTROLLERS}/controller.h
             ${SRC}/${CONTROLLERS}/controller.cpp
             ${SRC}/${CONTROLLERS}/micro_service_controller.h
             ${SRC}/${CONTROLLERS}/micro_service_controller.cpp)

configure_target_executable (${PROJECT_NAME} "${SOURCES}")