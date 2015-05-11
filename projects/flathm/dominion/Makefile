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

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

unittest: test1 test2 test3 test4 card1 card2 card3 card4

test1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

test2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

test3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

test4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

card1: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

card2: dominion.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

card3: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

card4: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	
unittestresults.out: dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c 
	echo "***********************unittestresults.out********************************" > unittestresults.out
	
	echo "****************************unittest1.c:*********************************" >> unittestresults.out
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo "****************************unittest1 Coverage***************************" >> unittestresults.out
	gcov unittest1.c.gcov -b >> unittestresults.out
	
	echo "****************************unittest2.c:*********************************" >> unittestresults.out
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "****************************unittest2 Coverage***************************" >> unittestresults.out
	gcov unittest2.c.gcov -b >> unittestresults.out
	
	echo "****************************unittest3.c**********************************" >> unittestresults.out
	gcc -o unittest3 unittest3.c  -g dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "****************************unittest3 Coverage***************************" >> unittestresults.out
	gcov unittest3.c.gcov -b >> unittestresults.out
	
	echo "****************************unittest4.c***********************************" >> unittestresults.out
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "****************************unittest4 Coverage***************************" >> unittestresults.out
	gcov unittest4.c.gcov -b >> unittestresults.out
	
	echo "****************************cardtest1.c**********************************" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "****************************cardtest1 Coverage***************************" >> unittestresults.out
	gcov cardtest1.c.gcov -b >> unittestresults.out

	echo "****************************cardtest2.c**********************************" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "****************************cardtest2 Coverage***************************" >> unittestresults.out
	gcov cardtest2.c.gcov -b >> unittestresults.out

	echo "****************************cardtest3.c**********************************" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "****************************cardtest3 Coverage***************************" >> unittestresults.out
	gcov cardtest3.c.gcov -b >> unittestresults.out

	echo "****************************cardtest4.c**********************************" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo "****************************cardtest4 Coverage****************************" >> unittestresults.out
	gcov cardtest4.c.gcov -b >> unittestresults.out
	
	echo "****************************dominion.c**********************************" >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "****************************END ****************************************" >> unittestresults.out
	