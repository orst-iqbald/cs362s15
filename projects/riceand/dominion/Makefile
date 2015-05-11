CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	echo "Random Test Adventurer Results:" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo "Coverage:" >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out

randomtestcard.out: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
	echo "Random Test Card (Outpost) Results:" >> randomtestcard.out
	./randomtestcard >> randomtestcard.out
	echo "Coverage:" >> randomtestcard.out
	gcov -f -b dominion.c >> randomtestcard.out

unittestresults.out: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	echo "Dominion Test Results (Assignment 3)" > unittestresults.out

	echo "Unit Test 1:" >> unittestresults.out
	gcc dominion.o rngs.o unittest1.c -o unittest1 $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Unit Test 2:" >> unittestresults.out
	gcc dominion.o rngs.o unittest2.c -o unittest2 $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Unit Test 3:" >> unittestresults.out
	gcc dominion.o rngs.o unittest3.c -o unittest3 $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Unit Test 4:" >> unittestresults.out
	gcc dominion.o rngs.o unittest4.c -o unittest4 $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Card Test 1:" >> unittestresults.out
	gcc dominion.o rngs.o cardtest1.c -o cardtest1 $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Card Test 2:" >> unittestresults.out
	gcc dominion.o rngs.o cardtest2.c -o cardtest2 $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Card Test 3:" >> unittestresults.out
	gcc dominion.o rngs.o cardtest3.c -o cardtest3 $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

	echo "Card Test 4:" >> unittestresults.out
	gcc dominion.o rngs.o cardtest4.c -o cardtest4 $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard
