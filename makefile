includeF = -Iinclude
libraryF = -Llib -lSDL2

bin/main: pre-build src/main.cpp obj/GameOfLife.o
	g++ -std=c++17 -o bin/main src/main.cpp obj/GameOfLife.o $(includeF) $(libraryF) 
	
obj/GameOfLife.o: src/GameOfLife.cpp
	g++ -std=c++17 -c -o obj/GameOfLife.o src/GameOfLife.cpp $(includeF) $(libraryF) 

pre-build: 
	mkdir -p obj && mkdir -p bin
