all: fsmatcher fs-gdb

fs-gdb: main1.o
	gcc -Wall -g main1.o -o0 -o fs-gdb

main1.o: main1.c
	gcc -Wall -c main1.c -o main1.o

fsmatcher: main.o func.o
	gcc -Wall main.o func.o -o fsmatcher
main.o: main.c
	gcc -Wall -c main.c -o main.o
func.o: func.c
	gcc -Wall -c func.c -o func.o
