cmake_minimum_required(VERSION 3.29)
project(Caso_Final_Integrador_4)

set(CMAKE_CXX_STANDARD 14)
# Incluir la carpeta json11
include_directories(${CMAKE_SOURCE_DIR}/json11)

add_library(json11 STATIC json11/json11.cpp) # libreria externa para manejo de json

add_executable(Caso_Final_Integrador_4 main.cpp
        Variant.hpp
        Variant.cpp
)
# Enlazar la libreria json11
target_link_libraries(Caso_Final_Integrador_4 PRIVATE json11)
set_target_properties(Caso_Final_Integrador_4 PROPERTIES LINK_FLAGS "-mconsole")