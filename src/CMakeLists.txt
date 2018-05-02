function (configure_target_executable target_name src)
    add_executable (${target_name} ${src})
    add_custom_command (TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CudaRouterLibrary_DIR}/$<$<CONFIG:Debug>:debug/>bin $<TARGET_FILE_DIR:${target_name}>)

    target_include_directories (${target_name} PRIVATE "${CudaRouterLibrary_INCLUDE_DIRS}" 
            PRIVATE ${INCLUDE_DIR})
    target_link_libraries (${target_name} PRIVATE cpprestsdk::cpprest
            optimized "${CudaRouterLibrary_LIBRARIES}"
            debug "${CudaRouterLibrary_LIBRARIES_DEB}"
            PRIVATE spdlog::spdlog PRIVATE fmt::fmt-header-only)
endfunction ()

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (HEADERS ${INCLUDE_DIR}/interrupts.h
        ${INCLUDE_DIR}/controller/controller.h
        ${INCLUDE_DIR}/controller/handler.h
        ${INCLUDE_DIR}/controller/router_controller.h
        ${INCLUDE_DIR}/controller/device_query_controller.h)
set (SOURCES server_launcher.cpp
        controller/controller.cpp
        controller/router_controller.cpp
        controller/device_query_controller.cpp)
set (EXE_SOURCES ${HEADERS} ${SOURCES})

configure_target_executable (${PROJECT_NAME} "${EXE_SOURCES}")
