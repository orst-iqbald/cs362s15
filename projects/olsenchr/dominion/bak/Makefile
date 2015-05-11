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

testGetCost: unittest1.c dominion.o rngs.o
	gcc -o testGetCost -g unittest1.c dominion.o rngs.o $(CFLAGS)


testGameOver: unittest2.c dominion.o rngs.o
	gcc -o testGameOver -g unittest2.c dominion.o rngs.o $(CFLAGS)

testBuyCard: unittest3.c dominion.o rngs.o
	gcc -o testBuyCard -g unittest3.c dominion.o rngs.o $(CFLAGS)

testGainCard: unittest4.c dominion.o rngs.o
	gcc -o testGainCard -g unittest4.c dominion.o rngs.o $(CFLAGS)

testSmithyCard: cardtest1.c dominion.o rngs.o
	gcc -o testSmithyCard -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testAdvCard: cardtest2.c dominion.o rngs.o
	gcc -o testAdvCard -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testRemodelCard: cardtest3.c dominion.o rngs.o
	gcc -o testRemodelCard -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testCutpurseCard: cardtest4.c dominion.o rngs.o
	gcc -o testCutpurseCard -g cardtest4.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

#unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
unittestresults.out: testGetCost testGameOver testBuyCard testGainCard testSmithyCard testAdvCard testRemodelCard testCutpurseCard
	./testGetCost >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	./testGameOver >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	./testBuyCard >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	./testGainCard >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	./testSmithyCard >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	./testAdvCard >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	./testRemodelCard >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	./testCutpurseCard >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	#gcc -o unittest1 unittest1.c $(CFLAGS)
	#unittest1 >> unittestresults.out
	#gcov unittest1.c >> unittestresults.out
	#gcc -o unittest2 unittest2.c $(CFLAGS)
	#unittest2 >> unittestresults.out
	#gcc -o unittest3 unittest3.c $(CFLAGS)
	#unittest3 >> unittestresults.out
	#gcc -o unittest4 unittest4.c $(CFLAGS)
	#unittest4 >> unittestresults.out
	#gcc -o cardtest1 cardtest1.c $(CFLAGS)
	#cardtest1 >> unittestresults.out
	#gcc -o cardtest2 cardtest2.c $(CFLAGS)
	#cardtest2 >> unittestresults.out
	#gcc -o cardtest3 cardtest3.c $(CFLAGS)
	#cardtest3 >> unittestresults.out
	#gcc -o cardtest4 cardtest4.c $(CFLAGS)
	#cardtest4 >> unittestresults.out
	


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
