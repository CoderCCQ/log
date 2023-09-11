cmake_minimum_required(VERSION 3.5)

project(log LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)
endif()

set(SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)

include_directories(${SRC_PATH})

file(GLOB SRC_FILES ${SRC_PATH}/*.cpp ${SRC_PATH}/*.h)
add_library(${PROJECT_NAME} ${SRC_FILES}


)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(example)
