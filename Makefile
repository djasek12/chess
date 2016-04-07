
all: 	bin/main

bin/main: bin/main.o bin/board.o bin/game.o bin/manager.o bin/pieces.o bin/AI.o bin/Move.o
		g++ main.o board.o game.o manager.o pieces.o AI.o Move.o -o main

bin/main.o: src/main.cpp
		g++ -c src/main.cpp
bin/board.o:  src/board.cpp
		g++ -c src/board.cpp
bin/game.o: src/game.cpp
		g++ -c src/game.cpp
bin/manager.o: src/manager.cpp
		g++ -c src/manager.cpp
bin/pieces.o: src/pieces.cpp
		g++ -c  src/pieces.cpp
bin/AI.o: src/AI.cpp
	g++ -c src/AI.cpp
bin/Move.o: src/Move.cpp
	g++ -c src/Move.cpp
clean:	
		rm -f *.o bin/main

