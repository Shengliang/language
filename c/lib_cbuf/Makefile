# ref: http://stackoverflow.com/questions/2734719/how-to-compile-a-static-library-in-linux
# ar rcs lib_xyz.a xyz.o
# r means to insert with replacement
# c means to create a new archive
# s means to write an index. 

lib_cbuf.a:
	gcc -c circular_buffer.c -o circular_buffer.o
	ar rcs lib_cbuf.a circular_buffer.o

test: lib_cbuf.a
	gcc circular_buffer_selftest.c lib_cbuf.a -o circular_buffer_selftest
	./circular_buffer_selftest

clean:
	@-rm lib_cbuf.a circular_buffer.o circular_buffer_selftest
