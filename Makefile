MAP = -DMAP
OBJ = StatLog.o ReadFile.o analog.o
FLAGS = -ansi -pedantic -Wall -std=c++11

analog: $(OBJ)
		g++ -o analog $(OBJ) $(MAP) $(FLAGS)

analog.o: analog.cpp
		g++ -c analog.cpp $(FLAGS)

StatLog.o: StatLog.cpp
		g++ -c StatLog.cpp $(FLAGS)

ReadFile.o: ReadFile.cpp
		g++ -c ReadFile.cpp $(FLAGS)

clean:
		rm -f $(OBJ) analog