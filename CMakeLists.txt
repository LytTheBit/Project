cmake_minimum_required(VERSION 3.21)
project(Reisende)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test) #<-aggiunto
set(SOURCE_FILES Token.cpp Token.h) #<-aggiunto
add_executable(Reisende main.cpp Librerie.h Librerie.cpp Game.cpp Game.h Arena.cpp Arena.h Token.cpp Token.h)
add_library(core ${SOURCE_FILES})#<-aggiunti
target_link_libraries(Reisende core)#<-aggiunti

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(Reisende sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

