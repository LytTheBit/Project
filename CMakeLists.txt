cmake_minimum_required(VERSION 3.21)
project(Reisende)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test) #<-aggiunto
set(SOURCE_FILES Token.cpp Token.h Librerie.h TurnSystem.cpp TurnSystem.h Graphics.cpp Graphics.h AStar.cpp AStar.h Text.cpp Text.h Strategy.cpp Strategy.h) #<-aggiunto
add_executable(Reisende main.cpp Librerie.h Game.cpp Game.h Screen.cpp Screen.h Token.cpp Token.h TurnSystem.cpp TurnSystem.h Graphics.cpp Graphics.h AStar.cpp AStar.h Text.cpp Text.h Strategy.cpp Strategy.h)
add_library(core ${SOURCE_FILES})#<-aggiunti
target_link_libraries(Reisende core)#<-aggiunti

set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR C:/SFML/lib/cmake/SFML)
set(SFML_DIR ./SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
#file(COPY "C:/SFML/bin/openal32.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "./SFML/bin/openal32.dll" DESTINATION ${CMAKE_BINARY_DIR})

#include_directories(C:/SFML/include)
include_directories(./SFML/include)
target_link_libraries(Reisende sfml-system sfml-window sfml-graphics sfml-audio sfml-network)