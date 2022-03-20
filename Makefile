SFML = -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
OPT = -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -std=c++17

# Name of the program file
TITLE = imperialism

OBJ = main.o

output: $(OBJ)
	g++ $(OBJ) -o $(TITLE) $(SFML) $(OPT)

main.o: main.cpp
	g++ -c main.cpp $(SFML) $(OPT)
