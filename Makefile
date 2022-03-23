SFML = -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
OPT = -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17

# Name of the program file
TITLE = imperialism

OBJ = main.o mapnode.o map.o textbutton.o game.o mainmenu.o

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
