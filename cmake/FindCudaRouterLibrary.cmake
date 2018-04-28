# Attempts to find CudaRouterLibrary which should normally be installed 
# in corresponding folder (x64) of program files on Windows platform.
#
# Once done this will define:
#  CudaRouterLibrary_DIR            - the root of the installed library
#  CudaRouterLibrary_FOUND          - library has been located
#  CudaRouterLibrary_INCLUDE_DIRS   - the CudaRouterLibrary include directories
#  CudaRouterLibrary_LIBRARIES      - The libraries needed to use CudaRouterLibrary (Release)
#  CudaRouterLibrary_LIBRARIES_DEB  - The libraries needed to use CudaRouterLibrary (Debug)

set (CudaRouterLibrary_FOUND FALSE)

if (WIN32)
    set (CudaRouterLibrary_DIR "$ENV{PROGRAMFILES}/cuda-vehicle-router")
    set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CudaRouterLibrary_DIR})
endif ()

find_path (CudaRouterLibrary_INCLUDE_DIRS NAMES router_library.h)
find_library (CudaRouterLibrary_LIBRARIES NAMES cuda-vehicle-router-lib)
find_library (CudaRouterLibrary_LIBRARIES_DEB NAMES cuda-vehicle-router-libd PATH_SUFFIXES debug/lib)

set (CudaRouterLibrary_FOUND TRUE)