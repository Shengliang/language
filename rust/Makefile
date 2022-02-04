PROG=guess_number

build: clean
	cargo new ${PROG}
	cp ${PROG}.rs ${PROG}/src/main.rs; cd ${PROG}; cargo add rand; cargo build; ls -al ./target/debug/${PROG}
		
run:
	./${PROG}/target/debug/${PROG}

clean:
	\rm -rf ${PROG}

