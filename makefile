all: bank

bank: bank.o structs.o functions.o
	gcc -pedantic -Wall -g $^ -o $@ -lm

bank.o: bank.c

structs.o: structs.h structs.c

functions.o: functions.h functions.c

clean:
	-rm bank.o structs.o functions.o bank

remake:
	make clean
	make