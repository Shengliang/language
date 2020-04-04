all:
	gcc -shared -fPIC  -o io_submit.so io_submit.c -ldl
	gcc -Wl,--wrap=io_submit -DTEST_WRAPPER main.c -o wtest -laio
	gcc main.c -o test -laio

run:
	./wtest
	chmod 644 /tmp/test
	cat /tmp/test

run1:
	./test
	chmod 644 /tmp/test
	cat /tmp/test

run2:
	LD_PRELOAD=./io_submit.so ./test
	chmod 644 /tmp/test
	cat /tmp/test

clean:
	rm -rf wtest
	rm -rf io_submit.so 
	rm -rf test
	rm -rf /tmp/test
