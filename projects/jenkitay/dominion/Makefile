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
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1.exe unittest1 unittest2.exe unittest2 unittest3.exe unittest3 unittest4.exe unittest4 cardtest1.exe cardtest1 cardtest2.exe cardtest2 cardtest3.exe cardtest3 cardtest4.exe cardtest4 testDrawCard.exe testDrawCard badTestDrawCard.exe badTestDrawCard unittestresults.out


unittestresults.out: mytests runmytests
	
mytests: utest1 utest2 utest3 utest4 ctest1 ctest2 ctest3 ctest4
	
utest1: unittest1.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) unittest1.c dominion.o rngs.o -o unittest1

utest2: unittest2.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) unittest2.c dominion.o rngs.o -o unittest2

utest3: unittest3.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) unittest3.c dominion.o rngs.o -o unittest3

utest4: unittest4.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) unittest4.c dominion.o rngs.o -o unittest4

ctest1: cardtest1.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) cardtest1.c dominion.o rngs.o -o cardtest1

ctest2: cardtest2.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) cardtest2.c dominion.o rngs.o -o cardtest2

ctest3: cardtest3.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) cardtest3.c dominion.o rngs.o -o cardtest3

ctest4: cardtest4.c dominion.o rngs.o
	gcc -g -std=c99 $(CFLAGS) cardtest4.c dominion.o rngs.o -o cardtest4

.IGNORE: runmytests
runmytests: 
	echo "*********************************************************" > unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      unittest1      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./unittest1 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  unittest1   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov unittest1 >> unittestresults.out
	echo " " >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      unittest2      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  unittest2   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov unittest2 >> unittestresults.out
	echo " " >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      unittest3      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  unittest3   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov unittest3 >> unittestresults.out
	echo " " >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      unittest4      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  unittest4   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov unittest4 >> unittestresults.out
	echo " " >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      cardtest1      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  cardtest1   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov cardtest1 >> unittestresults.out
	echo " " >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      cardtest2      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  cardtest2   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov cardtest2 >> unittestresults.out
	echo " " >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      cardtest3      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  cardtest3   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov cardtest3 >> unittestresults.out
	echo " " >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************      cardtest4      ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov  cardtest4   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov cardtest4 >> unittestresults.out
	echo " " >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************   gcov dominion.c   ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov dominion >> unittestresults.out
	echo " " >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "******************     gcov rngs.c     ******************" >> unittestresults.out
	echo "******************                     ******************" >> unittestresults.out
	echo "*********************************************************" >> unittestresults.out
	echo " " >> unittestresults.out
	gcov rngs >> unittestresults.out
	echo " " >> unittestresults.out
	cat rngs.c.gcov >> unittestresults.out
	echo " " >> unittestresults.out


	
	
	
	
	