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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
		
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Running Tests in dominion.c:" > unittestresults.out
	
	echo "+++ unittest1.c: +++" >> unittestresults.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "+++ unittest1.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ unittest2.c: +++" >> unittestresults.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "+++ unittest2.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ unittest3.c: +++" >> unittestresults.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "+++ unittest3.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ unittest4.c: +++" >> unittestresults.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "+++ unittest4.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ cardtest1.c: +++" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "+++ cardtest1.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ cardtest2.c: +++" >> unittestresults.out
	gcc -o cardtest2 dominion.o rngs.o cardtest2.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "+++ cardtest2.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ cardtest3.c: +++" >> unittestresults.out
	gcc -o cardtest3 dominion.o rngs.o cardtest3.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "+++ cardtest3.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
	echo "+++ cardtest4.c: +++" >> unittestresults.out
	gcc -o cardtest4 dominion.o rngs.o cardtest4.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "+++ cardtest4.c: gcov coverage +++" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	
randomtestresults: randomtestcard.c randomtestadventurer.c dominion.o rngs.o
	echo "Running Tests in dominion.c:"
	
	echo "+++ randomtestcard.c: +++" > randomtestcard.out
	gcc -o randomtestcard dominion.o rngs.o randomtestcard.c $(CFLAGS)
	./randomtestcard >> randomtestcard.out
	echo "+++ randomtestcard.c: gcov coverage +++" >> randomtestcard.out
	gcov dominion.c -b >> randomtestcard.out
	
	echo "+++ randomtestadventurer.c: +++" > randomtestadventurer.out
	gcc -o randomtestadventurer dominion.o rngs.o randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "+++ randomtestadventurer.c: gcov coverage +++" >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	
all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4  cardtest1 cardtest2 cardtest3 cardtest4 unittestresults randomtestcard randomtestadventurer randomtestresults

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittestresults randomtestcard randomtestadventurer randomtestresults
