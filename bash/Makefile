# How to write loop in a makefile?
# ref: http://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile

TESTS= 1 2 3 
run:
	@for I in $(TESTS) ; do \
          echo test$$I.bin test$$I.out;\
        done
	@echo
	@$(foreach I,$(TESTS),echo test$I.bin test$I.out;)

