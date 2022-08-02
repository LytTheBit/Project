cmake_minimum_required(VERSION 3.21)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#qui aggiungo sfml
#add_executable(ReisendeText runAllTests.cpp TokenSuite.cpp TokenTest.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
LINK_LIBRARIES(sfml-system sfml-window sfml-graphics sfml-audio)#<-aggiunto dopo
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)
#target_link_libraries(test sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

#include_directories(./Sprites)provo a caricare gli sprite
set(TEST_SOURCE_FILES runAllTests.cpp TokenTest.cpp TokenSuite.cpp TurnSystemSuite.cpp ../Librerie.cpp ../Librerie.h)
add_executable(runGameCharacterTests ${TEST_SOURCE_FILES})
target_link_libraries(runGameCharacterTests gtest gtest_main)

