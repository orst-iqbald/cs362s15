CC=gcc
FLAGS= -Wall -ftest-coverage -fprofile-arcs -lm

random: randomtestadventurer.c randomtestcard.c dominion.c rngs.c
	$(CC) -o randomtestadventurer.out randomtestadventurer.c dominion.c rngs.c $(FLAGS)
	$(CC) -o randomtestcard.out randomtestcard.c dominion.c rngs.c $(FLAGS)

clean:
	rm *.out *.gcno *.gcov *.gcda
