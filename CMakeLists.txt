cmake_minimum_required(VERSION 3.10)
project(bspEditor CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS 
    Widgets 
    OpenGL 
    OpenGLWidgets 
    Concurrent
    
)

set(VTFLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/VTFlib")
set(VTFLIB_LIB_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libs/VTFlib/x64/VTFLib.lib")
set(VTFLIB_DLL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libs/VTFlib/x64/VTFLib.dll")

add_library(VTFLib SHARED IMPORTED)
set_target_properties(VTFLib PROPERTIES
    # This MUST point to the .lib file for the linker to find the symbols
    IMPORTED_IMPLIB "${VTFLIB_LIB_FILE}"
    # This points to the .dll for runtime (optional but good practice)
    IMPORTED_LOCATION "${VTFLIB_DLL_FILE}"
    INTERFACE_INCLUDE_DIRECTORIES "${VTFLIB_INCLUDE_DIR}"
)

find_package(OpenGL REQUIRED)

add_executable(bspEditor src/app/main.cpp
    src/app/titanfall2bspData/enums.h src/app/titanfall2bspData/helperfunctions.h src/app/titanfall2bspData/structs.h
    src/app/titanfall2bspData/openGL.h src/app/titanfall2bspData/SettingsDialog.h src/app/titanfall2bspData/SettingsDialog.cpp  )

target_include_directories(bspEditor PRIVATE 
    src/app
    src/app/titanfall2bspData
)

target_link_libraries(bspEditor PRIVATE 
    Qt6::Widgets 
    Qt6::OpenGL 
    Qt6::OpenGLWidgets 
    Qt6::Concurrent
    OpenGL::GL
    VTFLib  
)


if(WIN32)
    add_custom_command(TARGET bspEditor POST_BUILD
        COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" $<TARGET_FILE:bspEditor>
    )


endif()