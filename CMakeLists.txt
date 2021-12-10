CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)

PROJECT(ChessMate)

SET(CMAKE_CXX_STANDART 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system")
add_executable(ChessMate project/src/main.cpp) # Define the target
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # Tell CMake where to find the module
find_package(SFML REQUIRED COMPONENTS graphics window system) # Look for SFML

include_directories(${SFML_INCLUDE_DIR}) # You forgot this line above; add SFML's include dir


target_link_libraries(ChessMate ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}) # Link SFML and dependencies
#Сделать с помощью make а не cmakeи с в тупую собирать через bash скрипты