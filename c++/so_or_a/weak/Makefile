CC=gcc
CFLAGS=-I. 
OBJ1 = a.o b.o main.o
OBJ2 = b.o a.o main.o
OBJ3 = main.o a.o b.o

OBJ4 = a.o main.o
OBJ5 = main.o a.o

OBJ6 = main.o 

EXE = prog1 prog2 prog3 prog4 prog5 prog6 prog7 prog8 prog67 prog76 prog678 prog687

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

liba.so: a.o 
	$(CC) -shared -o liba.so a.o $(CFLAGS)

libb.so: b.o 
	$(CC) -shared -o libb.so b.o $(CFLAGS)

libc.so: c.o 
	$(CC) -shared -o libc.so c.o $(CFLAGS)

%.a: %.o 
	ar -r -o $@ $< $(CFLAGS)

prog1: ${OBJ1}
	$(CC) -o $@ $^ $(CFLAGS)

prog2: ${OBJ2}
	$(CC) -o $@ $^ $(CFLAGS)

prog3: ${OBJ3}
	$(CC) -o $@ $^ $(CFLAGS)

prog4: ${OBJ4}
	$(CC) -o $@ $^ $(CFLAGS)

prog5: ${OBJ5}
	$(CC) -o $@ $^ $(CFLAGS)

prog6: ${OBJ6} liba.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -la

prog7: ${OBJ6} libb.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -lb

prog8: ${OBJ6} libc.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -lc

prog67: ${OBJ6} liba.so libb.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -la -lb

prog76: ${OBJ6} liba.so libb.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -lb -la

prog678: ${OBJ6} liba.so libb.so libc.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -la -lb -lc

prog687: ${OBJ6} liba.so libb.so libc.so
	$(CC) -o $@ ${OBJ6} $(CFLAGS) -L. -la -lc -lb

all: ${EXE} liba.so libb.so libc.so

clean:
	-rm -rf *.o  *.so 
	-rm -rf ${EXE}


run:
	for p in prog1 prog2 prog3 prog4 prog5 prog6 prog7 prog8 prog67 prog76 prog678 prog687; do  \
          echo run $$p; \
	  ./$$p; \
	done
