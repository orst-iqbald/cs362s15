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

unittestresults.out: unittest1.c dominion.o rngs.o
	gcc -o ut1 unittest1.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./ut1 >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	gcc -o ut2 unittest2.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./ut2 >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out	
	gcc -o ut3 unittest3.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./ut3 >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	gcc -o ut4 unittest4.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./ut4 >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	gcc -o c1 cardtest1.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./c1 >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out	
	gcc -o c2 cardtest2.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./c2 >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out	
	gcc -o c3 cardtest3.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./c3 >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	gcc -o c4 cardtest4.c dominion_helpers.h dominion.h dominion.c rngs.h rngs.c $(CFLAGS)
	./c4 >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out		

cleanprog:
	rm -f ut1 ut2 ut3 ut4 prog1 prog2 prog3 prog4 c1 c2 c3 c4

cleanout:
	rm -f unittestresults.out