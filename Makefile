# The makefile requires that the fann library has been built first and is either in the

GCC=gcc -I ../src/include -L ../src/

TARGETS =  thyroid_train thyroid_test
DEBUG_TARGETS = 

all: $(TARGETS)

%: %.c Makefile
	$(GCC) -O3 $< -o $@ -lfann -lm

%_fixed: %.c Makefile
	$(GCC) -O3 -DFIXEDFANN $< -o $@ -lfixedfann -lm

clean:
	rm -f $(TARGETS) $(DEBUG_TARGETS) xor_fixed.data *.net *~ *.obj *.exe *.tds noscale.txt withscale.txt scale_test_results.txt

quickcompiletest:
	gcc -O -ggdb -DDEBUG -Wall -Wformat-security -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wsign-compare -pedantic -ansi -I../src/ -I../src/include/ ../src/floatfann.c ../examples/xor_train.c -o ../examples/xor_train -lm 

debug: $(DEBUG_TARGETS)

%_debug: %.c Makefile ../src/*c ../src/include/*h
	$(GCC) -ggdb -DDEBUG -Wall -ansi -I../src/ -I../src/include/ ../src/floatfann.c $< -o $@ -lm 

%_fixed_debug: %.c Makefile ../src/*c ../src/include/*h
	$(GCC) -ggdb -DDEBUG -Wall -ansi -DFIXEDFANN -I../src/ -I../src/include/ ../src/fixedfann.c $< -o $@ -lm

rundebug: $(DEBUG_TARGETS)
	@echo
	@echo Training network
	valgrind --leak-check=yes --show-reachable=yes --leak-resolution=high --db-attach=yes ./xor_train_debug

	@echo
	@echo Testing network with floats
	valgrind --leak-check=yes --show-reachable=yes --leak-resolution=high --db-attach=yes ./xor_test_debug

	@echo
	@echo Testing network with fixed points
	valgrind --leak-check=yes --show-reachable=yes --leak-resolution=high --db-attach=yes ./xor_test_fixed_debug
