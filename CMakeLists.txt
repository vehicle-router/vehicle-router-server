cmake_minimum_required (VERSION 3.10 FATAL_ERROR)

project (vehicle-router-server)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package (cpprestsdk REQUIRED NAMES cpprestsdk cpprest)
find_package (CudaRouterLibrary REQUIRED)

add_subdirectory (src)