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

FILES = ~/Documents/School/Spring2015/CS362/cs362s15/projects/currymi/dominion/

unittestresults.out: 

	echo "Unit Tests" >> unittestsresults.out
	echo "==========" >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "unittest1.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/unittest1.c dominion.c rngs.c -o unittest1  $(CFLAGS) -I $(FILES)
	echo "Hello 1"
	./unittest1 >> unittestsresults.out
	echo "Hello"
	gcov unittest1 >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "unittest2.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/unittest2.c dominion.c rngs.c -o unittest2  $(CFLAGS) -I $(FILES)
	./unittest2 >> unittestsresults.out
	gcov unittest2 >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "unittest3.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/unittest3.c dominion.c rngs.c -o unittest3  $(CFLAGS) -I $(FILES)
	./unittest3 >> unittestsresults.out
	gcov unittest3 >> unittestsresults.out
	
	echo "" >> unittestsresults.out
	echo "unittest4.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/unittest4.c dominion.c rngs.c -o unittest4  $(CFLAGS) -I $(FILES)
	./unittest4 >> unittestsresults.out
	gcov unittest4 >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "cardTest1.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/cardTest1.c dominion.c rngs.c -o cardTest1 $(CFLAGS) -I $(FILES)
	./cardTest1 >> unittestsresults.out
	gcov cardTest1 >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "cardTest2.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/cardTest2.c dominion.c rngs.c -o cardTest2 $(CFLAGS) -I $(FILES)

	echo "" >> unittestsresults.out
	echo "cardTest3.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/cardTest3.c dominion.c rngs.c -o cardTest3 $(CFLAGS) -I $(FILES)
	./cardTest3 >> unittestsresults.out
	gcov cardTest3 >> unittestsresults.out

	echo "" >> unittestsresults.out
	echo "cardTest4.c:" >> unittestsresults.out
	echo "------------" >> unittestsresults.out
	gcc tests/unitTests/cardTest4.c dominion.c rngs.c -o cardTest4 $(CFLAGS) -I $(FILES)
	./cardTest4 >> unittestsresults.out
	gcov cardTest4 >> unittestsresults.out


all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardTest1 cardTest2 cardTest3 cardTest4 unittestresults.out unittestsresults.out
