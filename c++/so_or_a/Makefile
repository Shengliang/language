

add.cc:
	gcc -c add.cc -o add.o

add_bug.cc:
	gcc -c add_bug.cc -o add_bug.o

main.cc:
	gcc -c main.cc -o main.o


libadd.so: add.o
	gcc -shared add.o -o libadd.so

libadd_bug.so: add_bug.o
	gcc -shared add_bug.o -o libadd_bug.so


libadd.a: add.o
	ar -r libadd.a add.o

libadd_bug.a: add_bug.o
	ar -r libadd_bug.a add_bug.o


prog1a.e: libadd.a main.o
	gcc main.o libadd.a -o prog1a.e

prog1so.e: libadd.so main.o
	gcc main.o -L. -ladd -o prog1so.e

prog2a.e: libadd_bug.a main.o
	gcc main.o libadd_bug.a -o prog2a.e

prog2so.e: libadd_bug.so main.o
	gcc main.o -L. -ladd_bug -o prog2so.e

all: prog1a.e prog1so.e prog2a.e prog2so.e


test:
	@echo Use variables and fucntions from add.cc 20+21 = 41
	-./prog1a.e
	-./prog1so.e
	-./prog2a.e
	-./prog2so.e


clean:
	-rm -rf *.o *.a *.so *.e
