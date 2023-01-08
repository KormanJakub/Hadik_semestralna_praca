CC=gcc

all: prog

clean:
	rm -f *.o prog

.PHONY: all clean

prog: server.o client.o main.o game_snake.o
	$(CC) $^ -o $@ -pthread

server.o: server.c server.h game_snake.h
	$(CC) -c -o $@ -pthread
client.o: client.c client.h game_snake.h
	$(CC) -c -o $@ -pthread
game_snake.o: game_snake.c game_snake.h
	$(CC) -c -o $@ -pthread
main.o: main.c server.h client.h
	$(CC) -c -o $@ -pthread

client:
	./client localhost 10098 klient

server:
	./server 10098