# How to define your entry point without using stdlib?

all:
	gcc -e entry entry.c -o call_entry.exe
	@-./call_entry.exe || echo "Exit Code: $$?" 
	gcc entry.c -o call_main.exe
	@-./call_main.exe || echo "Exit Code: $$?" 
	gcc -e entry -nostdlib entry.c -o call_entry_nostdlib.exe
	@-./call_entry_nostdlib.exe || echo "Exit Code: $$?" 
	gcc main.c -o exit.exe
	@-./exit.exe || echo "Exit Code: $$?" 


clean:
	@rm call_entry.exe call_main.exe call_entry_nostdlib.exe exit.exe
