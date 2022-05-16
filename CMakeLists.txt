cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(imperialism VERSION 0.2)

IF(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.1 REQUIRED network audio graphics window system)

add_executable(imperialism src/credits.cpp src/game.cpp src/gamesettings.cpp 
                           src/gui.cpp src/hexvector.cpp src/imagebutton.cpp 
                           src/main.cpp src/mainmenu.cpp src/map.cpp src/mapnode.cpp 
                           src/options.cpp src/textbutton.cpp src/textinput.cpp 
                           src/texttoggle.cpp src/unit.cpp)
target_compile_options(imperialism PUBLIC -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion)
target_include_directories(imperialism PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${SFML_INCLUDE_DIR})
target_link_libraries(imperialism PUBLIC ${SFML_LIBRARIES} sfml-graphics sfml-system sfml-window)

