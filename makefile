all: bin/fsmatcher bin/fs-gdb

bin/fs-gdb: build/main.o build/fync.o
	gcc -Wall -g -o0 build/main.o build/fync.o -o bin/fs-gdb

bin/fsmatcher: build/main.o build/func.o
	gcc -Wall build/main.o build/func.o -o bin/fsmatcher

build/main.o: src/main.c
	gcc -Wall -c src/main.c -o build/main.o

build/func.o: src/func.c
	gcc -Wall -c src/func.c -o build/func.o

build/fync.o: src/fync.c
	gcc -Wall -c src/fync.c -o build/fync.o

.PHONY: clean

clean:
	rm -rf *.o
