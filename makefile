includeF = -Iinclude
libraryF = -Llib -lSDL2

bin/main.exe: src/main.cpp obj/GameOfLife.o
	g++ -std=c++17 -o bin/main.exe src/main.cpp obj/GameOfLife.o $(includeF) $(libraryF) 
	
obj/GameOfLife.o: src/GameOfLife.cpp
	g++ -std=c++17 -c -o obj/GameOfLife.o src/GameOfLife.cpp $(includeF) $(libraryF) 
