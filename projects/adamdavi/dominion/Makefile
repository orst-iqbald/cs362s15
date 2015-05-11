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

unittestresults.out: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	echo "Assignment 3: Results for running function and card unit tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out

randomtestcard.out: dominion.o rngs.o randomtestcard.c
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
	echo "Assignment 4: Results for random test from randomtestcard.c file:" > randomtestcard.out
	randomtestcard >> randomtestcard.out
	gcov dominion.c -b >> randomtestcard.out

randomtestadventurer.out: dominion.o rngs.o randomtestadventurer.c
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	echo "Assignment 4: Results for random test for adventurer card from randomtestadventurer.c file:" > randomtestadventurer.out
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out randomtestcard.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
	rm -f badTestDrawCard badTestDrawCard.exe testDrawCard testDrawCard.exe
	rm -f unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe
	rm -f cardtest1 cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe
	rm -f unittestresults.out
	rm -f randomtestcard randomtestcard.exe randomtestadventurer randomtestadventurer.exe
	rm -f randomtestcard.out randomtestadventurer.out
