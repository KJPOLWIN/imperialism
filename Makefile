SFML = -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
OPT = -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17

# Name of the program file
TITLE = imperialism

OBJ = main.o mapnode.o map.o

output: $(OBJ)
	g++ $(OBJ) -o $(TITLE) $(SFML) $(OPT)

clear: 
	rm $(OBJ) $(TITLE)

main.o: main.cpp
	g++ -c main.cpp $(SFML) $(OPT)
	
mapnode.o: mapnode.cpp mapnode.h
	g++ -c mapnode.cpp $(SFML) $(OPT)

map.o: map.h map.cpp mapnode.h
	g++ -c map.cpp $(SFML) $(OPT)
