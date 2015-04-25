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

unittest1: all unittest1.c
	gcc -std=c99 -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: all unittest2.c
	gcc -std=c99 -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: all unittest3.c
	gcc -std=c99 -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: all unittest4.c
	gcc -std=c99 -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtest1: all cardtest1.c
	gcc -std=c99 -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: all cardtest2.c
	gcc -std=c99 -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: all cardtest3.c
	gcc -std=c99 -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: all cardtest4.c
	gcc -std=c99 -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)


alltests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

cov1: unittest1
	./unittest1 > cov1.out
	gcov -b dominion.c >> cov1.out
	cat dominion.c.gcov >> cov1.out

cov2: unittest2
	./unittest2 > cov2.out
	gcov -b dominion.c >> cov2.out
	cat dominion.c.gcov >> cov2.out

cov3: unittest3
	./unittest3 > cov3.out
	gcov -b dominion.c >> cov3.out
	cat dominion.c.gcov >> cov3.out

cov4: unittest4
	./unittest4 > cov4.out
	gcov -b dominion.c >> cov4.out
	cat dominion.c.gcov >> cov4.out

cov5: cardtest1
	./cardtest1 > cov5.out
	gcov -b dominion.c >> cov5.out
	cat dominion.c.gcov >> cov5.out

cov6: cardtest2
	./cardtest2 > cov6.out
	gcov -b dominion.c >> cov6.out
	cat dominion.c.gcov >> cov6.out

cov7: cardtest3
	./cardtest3 > cov7.out
	gcov -b dominion.c >> cov7.out
	cat dominion.c.gcov >> cov7.out

cov8: cardtest4
	./cardtest4 > cov8.out
	gcov -b dominion.c >> cov8.out
	cat dominion.c.gcov >> cov8.out

allcoverage: cov1 cov2 cov3 cov4 cov5 cov6 cov7 cov8

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out
