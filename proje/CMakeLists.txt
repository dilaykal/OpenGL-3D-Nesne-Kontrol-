cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

include(CMakePrintHelpers)  
string(FIND ${CMAKE_CURRENT_SOURCE_DIR} / BaslangicIndeks REVERSE)
math(EXPR BaslangicIndeks "${BaslangicIndeks}+1")
string(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${BaslangicIndeks} -1 ProjeIsmi)

project(${ProjeIsmi})

set(Project_Dir ${CMAKE_SOURCE_DIR})

set(Kutuphane_Dir ${Project_Dir}/../../Kutuphaneler)

set(Project_Include_Dir ${Project_Dir}/include)

set(Project_Src_Dir ${Project_Dir}/src)

set(Project_Source_Files 
            ${Project_Src_Dir}/main.cpp
            ${Project_Src_Dir}/glad.c
            ${Project_Src_Dir}/shaderprogram.cpp
            ${Project_Src_Dir}/vertexbuffer.cpp       
            ${Project_Src_Dir}/vertexarrayobject.cpp        
            ${Project_Src_Dir}/GLWindow.cpp       
            ${Project_Src_Dir}/texturemanager.cpp      
            ${Project_Src_Dir}/indexbuffer.cpp        
            ${Project_Src_Dir}/shapecreator.cpp 
            ${Project_Src_Dir}/statemanager.cpp                                   

    )

include_directories(
    ${Project_Include_Dir}
    ${Kutuphane_Dir}/glm
    ${Kutuphane_Dir}/stb
      
    )


set(glfw3_DIR ${Kutuphane_Dir}/glfw/lib/cmake/glfw3/)

find_package(glfw3 3.4 REQUIRED)

add_executable(${PROJECT_NAME} ${Project_Source_Files})

target_link_libraries(${PROJECT_NAME} glfw)

