all: 
	gcc -c logging.c -o logging.o
	gcc -c message.c -o message.o
	g++ -std=c++17 -Wall -Wextra -c bgame.cpp -o bgame.o
	g++ -std=c++17 -Wall -Wextra bgame.o message.o logging.o -o bgame

clean:
	rm -f bgame *.o

