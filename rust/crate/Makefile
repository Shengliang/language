
all:
	rustc --crate-type=lib rary.rs
	ls -l lib*
	rustc main.rs --extern rary=library.rlib --edition=2021 && ./main


clean:
	rm library.rlib
	rm main
