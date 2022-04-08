SFML = -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
OPT = -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17

# Name of the program file
TITLE = imperialism

OBJ = main.o mapnode.o map.o textbutton.o game.o mainmenu.o gamesettings.o textinput.o unit.o gui.o options.o credits.o imagebutton.o

output: $(OBJ)
	g++ $(OBJ) -o $(TITLE) $(SFML) $(OPT)

clear: 
	rm $(OBJ) $(TITLE)

main.o: src/main.cpp src/game.h src/mainmenu.h
	g++ -c src/main.cpp $(SFML) $(OPT)
	
mapnode.o: src/mapnode.cpp src/mapnode.h
	g++ -c src/mapnode.cpp $(SFML) $(OPT)

map.o: src/map.h src/map.cpp src/mapnode.h
	g++ -c src/map.cpp $(SFML) $(OPT)

textbutton.o: src/textbutton.h src/textbutton.cpp
	g++ -c src/textbutton.cpp $(SFML) $(OPT)

game.o: src/game.h src/game.cpp src/textbutton.h src/map.h
	g++ -c src/game.cpp $(SFML) $(OPT)

mainmenu.o: src/mainmenu.h src/mainmenu.cpp src/textbutton.h
	g++ -c src/mainmenu.cpp $(SFML) $(OPT)

gamesettings.o: src/gamesettings.h src/gamesettings.cpp src/textbutton.h
	g++ -c src/gamesettings.cpp $(SFML) $(OPT)

textinput.o: src/textinput.h src/textinput.cpp 
	g++ -c src/textinput.cpp $(SFML) $(OPT)

unit.o: src/unit.h src/unit.cpp
	g++ -c src/unit.cpp $(SFML) $(OPT)

gui.o: src/gui.h src/gui.cpp
	g++ -c src/gui.cpp $(SFML) $(OPT)

options.o: src/options.h src/options.cpp src/textbutton.h
	g++ -c src/options.cpp $(SFML) $(OPT)

credits.o: src/credits.h src/credits.cpp src/textbutton.h
	g++ -c src/credits.cpp $(SFML) $(OPT)

imagebutton.o: src/imagebutton.h src/imagebutton.cpp
	g++ -c src/imagebutton.cpp $(SFML) $(OPT)
