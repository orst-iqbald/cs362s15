CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

#testDrawCard: testDrawCard.c dominion.o rngs.o
	#gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	#gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

#testBuyCard: testDrawCard.c dominion.o rngs.o
	#gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#testAll: dominion.o testSuite.c
	#gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

#runtests: testDrawCard 
	#./testDrawCard &> unittestresult.out
	#gcov dominion.c >> unittestresult.out
	#cat dominion.c.gcov >> unittestresult.out

runrandomtests: randomtestadventurer randomtestcard
	./randomtestadventurer > randomtestadventurer.out
	./randomtestcard > randomtestcard.out
	gcov -b dominion.c >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestcard.out
	
rununittests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest4
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
coverall: coverage1 coverage2 coverage3 coverage4 coverage5 coverage6 coverage7 coverage8

coverage1: unittest1
	./unittest1 > c1.out
	gcov -b dominion.c >> c1.out
	cat dominion.c.gcov >> c1.out

coverage2: unittest2
	./unittest2 > c2.out
	gcov -b dominion.c >> c2.out
	cat dominion.c.gcov >> c2.out

coverage3: unittest3
	./unittest3 > c3.out
	gcov -b dominion.c >> c3.out
	cat dominion.c.gcov >> c3.out

coverage4: unittest4
	./unittest4 > c4.out
	gcov -b dominion.c >> c4.out
	cat dominion.c.gcov >> c4.out

coverage5: cardtest1
	./cardtest1 > c5.out
	gcov -b dominion.c >> c5.out
	cat dominion.c.gcov >> c5.out	

coverage6: cardtest2
	./cardtest2 > c6.out
	gcov -b dominion.c >> c6.out
	cat dominion.c.gcov >> c6.out

coverage7: cardtest3
	./cardtest3 > c7.out
	gcov -b dominion.c >> c7.out
	cat dominion.c.gcov >> c7.out

coverage8: cardtest4
	./cardtest4 > c8.out
	gcov -b dominion.c >> c8.out
	cat dominion.c.gcov >> c8.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

#all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard *.out

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
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -Wall -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -Wall -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)	
	
randoms: randomtestadventurer randomtestcard