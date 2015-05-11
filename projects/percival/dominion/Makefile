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
	
randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	echo "Results for randomtestadventurer:" > randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo "Coverage results:" >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestcard.out: randomtestcard.c dominion.o rngs.o
	gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
	echo "Results for randomtestcard:" > randomtestcard.out
	./randomtestcard >> randomtestcard.out
	echo "Coverage results:" >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	
unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "unittest1:" > unittestresults.out
	./unittest1 >> unittestresults.out
	echo "unittest2:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "unittest3:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "unittest4:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "cardtest1:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "cardtest2:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "cardtest3:" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "cardtest4:" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo "Overall coverage results:" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
# There doesn't seem to be a way to put the individual coverage for each test
# into unittestersults.out, just the cumulative coverage. Therefore, I used
# the following rules to see the individual coverage for each test.
# You have to clean up the gcov files and recompile to get new data for each.
unit1covg: unittest1
	./unittest1 > unit1covg.out
	gcov -b dominion.c >> unit1covg.out
	cat dominion.c.gcov >> unit1covg.out
	
unit2covg: unittest2
	./unittest2 > unit2covg.out
	gcov -b dominion.c >> unit2covg.out
	cat dominion.c.gcov >> unit2covg.out
	
unit3covg: unittest3
	./unittest3 > unit3covg.out
	gcov -b dominion.c >> unit3covg.out
	cat dominion.c.gcov >> unit3covg.out
	
unit4covg: unittest4
	./unittest4 > unit4covg.out
	gcov -b dominion.c >> unit4covg.out
	cat dominion.c.gcov >> unit4covg.out
	
card1covg: cardtest1
	./cardtest1 > card1covg.out
	gcov -b dominion.c >> card1covg.out
	cat dominion.c.gcov >> card1covg.out
	
card2covg: cardtest2
	./cardtest2 > card2covg.out
	gcov -b dominion.c >> card2covg.out
	cat dominion.c.gcov >> card2covg.out
	
card3covg: cardtest3
	./cardtest3 > card3covg.out
	gcov -b dominion.c >> card3covg.out
	cat dominion.c.gcov >> card3covg.out
	
card4covg: cardtest4
	./cardtest4 > card4covg.out
	gcov -b dominion.c >> card4covg.out
	cat dominion.c.gcov >> card4covg.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard
