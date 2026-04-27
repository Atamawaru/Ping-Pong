all: build run

build: ping_pong.c
	gcc -Wall -Werror ping_pong.c -lSDL3 -o ping_pong

run: build
	./ping_pong
