cmake_minimum_required (VERSION 2.8)
project(ignite_demo)

set(RECORDS_VERSION_MAJOR 1)
set(RECORDS_VERSION_MINOR 0)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories($ENV{JAVA_HOME}/include/)
include_directories($ENV{JAVA_HOME}/include/linux/)
include_directories(/usr/local/include/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/common/os/linux/include/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/jni/include/)
include_directories($ENV{IGNITE_HOME}/platforms/cpp/core/include/)


link_directories(/usr/local/lib)
link_directories($ENV{JAVA_HOME}/jre/lib/amd64/server)

foreach(appsrc ${SOURCES})
    string(REPLACE ".cpp" "" apps ${appsrc})
    string(REPLACE "${PROJECT_SOURCE_DIR}/src/" "" app ${apps})
    message("--- " ${app})

    add_executable(${app} ${appsrc})
    target_link_libraries(${app} -lrt -ldl -lm -lpthread -rdynamic)
    target_link_libraries(${app} "$ENV{JAVA_HOME}/jre/lib/amd64/server/libjvm.so")
    target_link_libraries(${app} "/usr/local/lib/libignite.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-common.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-jni.so")
    target_link_libraries(${app} "/usr/local/lib/libignite-binary.so")
endforeach()


