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

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

fullcoverage: coverage1 coverage2 coverage3 coverage4 coverage5 coverage6 coverage7 coverage8

coverage1: unittest1
	./unittest1 > res1.out
	gcov -b dominion.c >> res1.out
	cat dominion.c.gcov >> res1.out

coverage2: unittest2
	./unittest2 > res2.out
	gcov -b dominion.c >> res2.out
	cat dominion.c.gcov >> res2.out

coverage3: unittest3
	./unittest3 > res3.out
	gcov -b dominion.c >> res3.out
	cat dominion.c.gcov >> res3.out

coverage4: unittest4
	./unittest4 > res4.out
	gcov -b dominion.c >> res4.out
	cat dominion.c.gcov >> res4.out

coverage5: cardtest1
	./cardtest1 > res5.out
	gcov -b dominion.c >> res5.out
	cat dominion.c.gcov >> res5.out	

coverage6: cardtest2
	./cardtest2 > res6.out
	gcov -b dominion.c >> res6.out
	cat dominion.c.gcov >> res6.out

coverage7: cardtest3
	./cardtest3 > res7.out
	gcov -b dominion.c >> res7.out
	cat dominion.c.gcov >> res7.out

coverage8: cardtest4
	./cardtest4 > res8.out
	gcov -b dominion.c >> res8.out
	cat dominion.c.gcov >> res8.out

unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: dominion.o rngs.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o rngs.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o rngs.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o rngs.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

randomtestadventurer: dominion.o rngs.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard: dominion.o rngs.o randomtestcard.c
	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard.out: randomtestcard
	./randomtestcard > randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer