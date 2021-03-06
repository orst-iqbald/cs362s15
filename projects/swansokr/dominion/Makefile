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

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	echo "Results for unittests and cardtests:" >> unittestresults.out
	
	echo -e "\nunittest1.c" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	
	echo -e "\nunittest2.c" >> unittestresults.out
	unittest2 >> unittestresults.out
	
	echo "unittest3.c" >> unittestresults.out
	unittest3 >> unittestresults.out
	
	echo -e "\nunittest4.c" >> unittestresults.out
	unittest4 >> unittestresults.out
	
	echo -e "\ncardtest1.c" >> unittestresults.out
	cardtest1 >> unittestresults.out
	
	echo -e "\ncardtest2.c" >> unittestresults.out
	cardtest2 >> unittestresults.out
	
	echo -e "\ncardtest3.c" >> unittestresults.out
	cardtest3 >> unittestresults.out
	
	echo -e "\ncardtest4.c" >> unittestresults.out
	cardtest4 >> unittestresults.out
	
	echo -e "\nCoverage for all tests:\n" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out	

rta: randomtestadventurer.c dominion.o rngs.o
	gcc -o rta randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	echo "Results for randomtestadventurer:" >> randomtestadventurer.out
	gcc -o rta randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	rta >> randomtestadventurer.out
	
	echo -e "\nCoverage for tests:\n" >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out

rtc: randomtestcard.c dominion.o rngs.o
	gcc -o rtc randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestcard.out: randomtestcard.c dominion.o rngs.o
	echo "Results for randomtestcard:" >> randomtestcard.out
	gcc -o rtc randomtestcard.c dominion.o rngs.o $(CFLAGS)
	rtc >> randomtestcard.out
	
	echo -e "\nCoverage for tests:\n" >> randomtestcard.out
	gcov dominion.c -b >> randomtestcard.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 rta rtc unittestresults.out

clean:
	rm -f *.out *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
