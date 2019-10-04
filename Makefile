TFILE := data/ex.mtx
#DEBUG = -DDEBUG

all: minimize maximize alpha iter eps

testall: clean testsmall testberlim testrandom

testsmall: all
	./minimize data/ex.mtx
	./maximize data/ex.mtx

testberlim: all
	./minimize data/berlin52.mtx
	./maximize data/berlin52.mtx

testrandom: all
	./minimize random
	./maximize random

minimize:
	gcc  $(DEBUG) -O3 -o minimize minimize.c io.c matrix.c heur.c tictac.c sa.c -lm

maximize:
	gcc  $(DEBUG) -O3 -o maximize maximize.c io.c matrix.c heur.c tictac.c sa.c -lm

alpha:
	gcc  $(DEBUG) -O3 -o alpha param_tests_alpha.c io.c matrix.c heur.c tictac.c sa.c -lm

iter:
	gcc  $(DEBUG) -O3 -o iter param_tests_iter.c io.c matrix.c heur.c tictac.c sa.c -lm

eps:
	gcc  $(DEBUG) -O3 -o eps param_tests_eps.c io.c matrix.c heur.c tictac.c sa.c -lm


clean:
	rm -rf minimize maximize alpha iter eps *.o

valg: all
	valgrind --leak-check=full ./minimize data/ex.mtx
	valgrind --leak-check=full ./maximize data/ex.mtx
	valgrind --leak-check=full ./alpha data/ex.mtx
	valgrind --leak-check=full ./iter data/ex.mtx
	valgrind --leak-check=full ./eps data/ex.mtx
