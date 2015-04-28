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
	
unitTest.o: dominion.o rngs.o
	gcc -c unitTest1.c $(CFLAGS)
	gcc -c unitTest2.c $(CFLAGS)
	gcc -c unitTest3.c $(CFLAGS)
	gcc -c unitTest4.c $(CFLAGS)
	gcc -c cardTest1.c $(CFLAGS)
	gcc -c cardTest2.c $(CFLAGS)
	gcc -c cardTest3.c $(CFLAGS)
	gcc -c cardTest4.c $(CFLAGS)
	
unitTest: unitTest.o
	gcc -o unitTest1 unitTest1.o dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest2 unitTest2.o dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest3 unitTest3.o dominion.o rngs.o $(CFLAGS)
	gcc -o unitTest4 unitTest4.o dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest1 cardTest1.o dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest2 cardTest2.o dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest3 cardTest3.o dominion.o rngs.o $(CFLAGS)
	gcc -o cardTest4 cardTest4.o dominion.o rngs.o $(CFLAGS)

runUnitTests: unitTest
	./unitTest1 > uTest1.txt
	./unitTest2 > uTest2.txt
	./unitTest3 > uTest3.txt
	./unitTest4 > uTest4.txt
	./cardTest1 > cTest1.txt
	./cardTest2 > cTest2.txt
	./cardTest3 > cTest3.txt
	./cardTest4 > cTest4.txt
	
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
