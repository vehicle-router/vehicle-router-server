function (configure_target_executable target_name src)
    add_executable (${target_name} ${src})
    add_custom_command (TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CudaRouterLibrary_DIR}/$<$<CONFIG:Debug>:debug/>bin $<TARGET_FILE_DIR:${target_name}>)

    target_include_directories (${target_name} PRIVATE "${CudaRouterLibrary_INCLUDE_DIRS}" 
            PRIVATE ${INCLUDE_DIR})
    target_link_libraries (${target_name} PRIVATE cpprestsdk::cpprest
            optimized "${CudaRouterLibrary_LIBRARIES}"
            debug "${CudaRouterLibrary_LIBRARIES_DEB}"
            PRIVATE spdlog::spdlog 
            PRIVATE fmt::fmt-header-only
            PRIVATE ${Boost_SYSTEM_LIBRARY})
endfunction ()

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (HEADERS 
        ${INCLUDE_DIR}/interrupts.h
        ${INCLUDE_DIR}/controller/controller.h
        ${INCLUDE_DIR}/controller/handler.h
        ${INCLUDE_DIR}/controller/router_controller.h
        ${INCLUDE_DIR}/controller/device_query_controller.h
        ${INCLUDE_DIR}/network/network_utils.h)
set (SOURCES 
        server_launcher.cpp
        controller/controller.cpp
        controller/router_controller.cpp
        controller/device_query_controller.cpp
        network/network_utils.cpp)
set (EXE_SOURCES ${HEADERS} ${SOURCES})

source_group (TREE ${PROJECT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})
source_group (TREE ${PROJECT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})

configure_target_executable (${PROJECT_NAME} "${EXE_SOURCES}")
