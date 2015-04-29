CC=gcc
FLAGS= -Wall -ftest-coverage -fprofile-arcs -lm

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Results of unittests for assignment 3:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	$(CC) -o unittest1 unittest1.c dominion.c rngs.c $(FLAGS)
	unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest2.c" >> unittestresults.out
	$(CC) -o unittest2 unittest2.c dominion.c rngs.c $(FLAGS)
	unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest3.c" >> unittestresults.out
	$(CC) -o unittest3 unittest3.c dominion.c rngs.c $(FLAGS)
	unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest4.c" >> unittestresults.out
	$(CC) -o unittest4 unittest4.c dominion.c rngs.c $(FLAGS)
	unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest1.c" >> unittestresults.out
	$(CC) -o cardtest1 cardtest1.c dominion.c rngs.c $(FLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest2.c" >> unittestresults.out
	$(CC) -o cardtest2 cardtest2.c dominion.c rngs.c $(FLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest3.c" >> unittestresults.out
	$(CC) -o cardtest3 cardtest3.c dominion.c rngs.c $(FLAGS)
	cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest4.c" >> unittestresults.out
	$(CC) -o cardtest4 cardtest4.c dominion.c rngs.c $(FLAGS)
	cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

clean:
	rm unittestresults.out

cleanall: 
	rm unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcno *.gcda *.gcov


