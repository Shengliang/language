all:
	gcc -g -c -fPIC -Wall mod1.c mod2.c mod3.c mod1_alt.c
	gcc -g -shared -o libalt.so mod1_alt.o 
	gcc -g -shared -Wl,-soname,libbar.so -o libfoo.so mod1.o mod2.o mod3.o
	ln -fs libfoo.so libbar.so
	gcc -g -Wall -o prog prog.c libfoo.so
	LD_LIBRARY_PATH=. ./prog
	# or use /etc/ld.so.preload
	LD_PRELOAD=libalt.so LD_LIBRARY_PATH=. ./prog
	

clean:
	\rm -rf *.so *.o prog
