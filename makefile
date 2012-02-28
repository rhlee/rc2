all:
	gcc -g main.c -o main `pkg-config --cflags --libs x11 xtst`