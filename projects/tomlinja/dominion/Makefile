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

testWhoseTurn: unittest1.c dominion.o rngs.o
	gcc -o testWhoseTurn -g unittest1.c dominion.o rngs.o $(CFLAGS)

testKingdomCards: unittest2.c dominion.o rngs.o
	gcc -o testKingdomCards -g unittest2.c dominion.o rngs.o $(CFLAGS)

testNumHandCards: unittest3.c dominion.o rngs.o
	gcc -o testNumHandCards -g unittest3.c dominion.o rngs.o $(CFLAGS)

testIsGameOver: unittest4.c dominion.o rngs.o
	gcc -o testIsGameOver -g unittest4.c dominion.o rngs.o $(CFLAGS)

testPlaySmithy: cardtest1.c dominion.o rngs.o
	gcc -o testPlaySmithy -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testPlayCouncilRoom: cardtest2.c dominion.o rngs.o
	gcc -o testPlayCouncilRoom -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testPlayVillage: cardtest3.c dominion.o rngs.o
	gcc -o testPlayVillage -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testPlayAdventurer: cardtest4.c dominion.o rngs.o
	gcc -o testPlayAdventurer -g cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Result for running unit tests:" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.o rngs.o cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

testPlayAdventurerRandom: randomtestadventurer.c dominion.o rngs.o
	gcc -o testPlayAdventurerRandom -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	echo "Result for running random adventurer tests:" > randomtestadventurer.out
	
	gcc -o randomtestadventurer dominion.o rngs.o randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out 2>&1
	gcov dominion.c >> randomtestadventurer.out 2>&1

testPlayVillageRandom: randomtestcard.c dominion.o rngs.o
	gcc -o testPlayVillageRandom -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestcard.out: randomtestcard.c dominion.o rngs.o
	echo "Result for running random village tests:" > randomtestcard.out
	
	gcc -o randomtestcard dominion.o rngs.o randomtestcard.c $(CFLAGS)
	randomtestcard >> randomtestcard.out 2>&1
	gcov dominion.c >> randomtestcard.out 2>&1

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

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
