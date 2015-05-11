CFLAGS = -Wall -fpic -coverage -lm

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
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out:
	make all
	./unittest1
	echo UNIT TEST 1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./unittest2
	echo UNIT TEST 2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./unittest3
	echo UNIT TEST 3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./unittest4
	echo UNIT TEST 4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./cardtest1
	echo CARD TEST 1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./cardtest2
	echo CARD TEST 2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./cardtest3
	echo CARD TEST 3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	make clean
	make all
	./cardtest4
	echo CARD TEST 4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	rm *.gcov
	
	
randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard.out: randomtestcard.c dominion.o rngs.o
	make all
	./randomtestcard
	echo SMITHY TEST >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	gcov -fb dominion.c >> randomtestcard.out
	rm *.gcov
	
randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	make all
	./randomtestadventurer
	echo ADVENTURER TEST >> randomtestadventurer.out
	echo -b dominion.c >> randomtestadventurer.out
	echo -fb dominion.c >> randomtestadventurer.out
	rm *.gcov

	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

oldAll: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so