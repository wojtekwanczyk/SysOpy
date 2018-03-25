
CC=gcc -Wall -std=c11
OPT = 0


static: sblocks.h dblocks.h
	$(CC) -c sblocks.c dblocks.c -O$(OPT)
	ar rcs libdblocks.a dblocks.o
	ar rcs libsblocks.a sblocks.o
	$(CC) -c -static main.c -O$(OPT)
	$(CC) main.o libdblocks.a libsblocks.a -o program


shared: sblocks.h dblocks.h 
	$(CC) -fPIC -shared dblocks.c sblocks.c -o libblocks.so
	$(CC) main.c -L. -Wl,-rpath=. -lblocks -o program



dynamic: sblocks.h dblocks.h
	$(CC) -fPIC -shared dblocks.c sblocks.c -o libblocks.so
	$(CC) dmain.c  -ldl -o dprogram


clean:
	rm -f *.o *.a *.so program dprogram




static3: static tests


shared3: shared tests


dynamic3: dynamic dtests



tests: 
	./program 1000 1000 dynamic create calloc deladdrep 500
	./program 1000 1000 static create malloc search 500
	./program 1000 1000 static create calloc add 5 500 delete 5 500
	./program 1000 1000 dynamic create calloc search 400

dtests: 
	./dprogram 1000 1000 dynamic create calloc deladdrep 500
	./dprogram 1000 1000 static create malloc search 500
	./dprogram 1000 1000 static create calloc add 5 500 delete 5 500
	./dprogram 1000 1000 dynamic create calloc search 500




















