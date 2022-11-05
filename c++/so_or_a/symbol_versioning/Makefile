all:
	gcc -g -c -fPIC -Wall sv_lib_v1.c
	gcc -g -shared -o libsv.so sv_lib_v1.o -Wl,--version-script,sv_v1.map
	gcc -g -o p1 sv_prog.c libsv.so
	gcc -g -c -fPIC -Wall sv_lib_v2.c
	gcc -g -shared -o libsv.so sv_lib_v2.o -Wl,--version-script,sv_v2.map
	gcc -g -o p2 sv_prog.c libsv.so

run:
	LD_LIBARY_PATH=. ./p2
	LD_LIBARY_PATH=. ./p1
	objdump -t p1 |grep xyz
	objdump -t p2 |grep xyz

clean:
	\rm p1 p2 *.o *.so
