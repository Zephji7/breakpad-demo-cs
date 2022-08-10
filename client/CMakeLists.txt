cmake_minimum_required(VERSION 3.0)

# find vcpkg home directory
if(DEFINED ENV{VCPKG_HOME})
      message("FOUND VCPKG: $ENV{VCPKG_HOME}")
      set(VCPKG_HOME $ENV{VCPKG_HOME}) #设置使用vcpkg的路径
      set(CMAKE_TOOLCHAIN_FILE "${VCPKG_HOME}\\scripts\\buildsystems\\vcpkg.cmake")
else()
      message("VCPKG_HOME NOT FOUND")
      
endif()

project(WindowsPipeClient)

#include breakpad
find_package(unofficial-breakpad CONFIG REQUIRED)
include_directories(${VCPKG_HOME}/packages/breakpad_x64-windows/include)
link_directories(${VCPKG_HOME}/packages/breakpad_x64-windows/lib)

#include glog
find_package(glog CONFIG REQUIRED)
include_directories(${VCPKG_HOME}/packages/glog_x64-windows/include)
link_directories(${VCPKG_HOME}/packages/glog_x64-windows/lib)

add_executable(${PROJECT_NAME}  ./main.cpp)
target_link_libraries(${PROJECT_NAME}
      PRIVATE unofficial::breakpad::libbreakpad unofficial::breakpad::libbreakpad_client glog::glog
)

