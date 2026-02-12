cmake_minimum_required(VERSION 3.10)

project(bspEditor CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(bspEditor src/app/main.cpp)

target_link_libraries(bspEditor PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)