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

runtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	gcov unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
  
coverall: unit1coverage unit2coverage unit3coverage unit4coverage card1coverage card2coverage card3coverage card4coverage
  
unit1coverage: unittest1
	./unittest1 > unit1cov.out
	gcov -b dominion.c >> unit1cov.out
	cat dominion.c.gcov >> unit1cov.out
  
unit2coverage: unittest2
	./unittest2 > unit2cov.out
	gcov -b dominion.c >> unit2cov.out
	cat dominion.c.gcov >> unit2cov.out
  
unit3coverage: unittest3
	./unittest3 > unit3cov.out
	gcov -b dominion.c >> unit3cov.out
	cat dominion.c.gcov >> unit3cov.out
  
unit4coverage: unittest4
	./unittest4 > unit4cov.out
	gcov -b dominion.c >> unit4cov.out
	cat dominion.c.gcov >> unit4cov.out
  
card1coverage: cardtest1
	./cardtest1 > card1cov.out
	gcov -b dominion.c >> card1cov.out
	cat dominion.c.gcov >> card1cov.out
  
card2coverage: cardtest2
	./cardtest2 > card2cov.out
	gcov -b dominion.c >> card2cov.out
	cat dominion.c.gcov >> card2cov.out
  
card3coverage: cardtest3
	./cardtest3 > card3cov.out
	gcov -b dominion.c >> card3cov.out
	cat dominion.c.gcov >> card3cov.out
  
card4coverage: cardtest4
	./cardtest4 > card4cov.out
	gcov -b dominion.c >> card4cov.out
	cat dominion.c.gcov >> card4cov.out
  
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
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

coverallrand: randadvcov randcardcov

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
  
randadvcov: randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
  
randomtestcard: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
  
randcardcov: randomtestcard
	./randomtestcard > randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
  
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer

