CFLAGS = -Wall -fpic -coverage -lm
EXECS = playdom test testInit badTestDrawCard testDrawCard unittest1 unittest2 \
		unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardtests: cardtest1 cardtest2 cardtest3 cardtest4

unittests: unittest1 unittest2 unittest3 unittest4

testresults: unittests cardtests
	echo "/* ---------------------------------------- */" > unittestresults.out
	-./unittest1 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./unittest2 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./unittest3 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./unittest4 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./cardtest1 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./cardtest2 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./cardtest3 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out
	-./cardtest4 >> unittestresults.out
	echo "/* --------------------------------------- */" >> unittestresults.out

gcovunit1: unittest1
	./unittest1
	gcov -abcf dominion.c > coveru1.out
	cat dominion.c.gcov >> coveru1.out
	rm -f *.gcov *.so
	
gcovunit2: unittest2
	./unittest2
	gcov -abcf dominion.c > coveru2.out
	cat dominion.c.gcov >> coveru2.out
	rm -f *.gcov *.so

gcovunit3: unittest3
	./unittest3
	gcov -abcf dominion.c > coveru3.out
	cat dominion.c.gcov >> coveru3.out
	rm -f *.gcov *.so

gcovunit4: unittest4
	./unittest4
	gcov -abcf dominion.c > coveru4.out
	cat dominion.c.gcov >> coveru4.out
	rm -f *.gcov *.so

gcovcard1: cardtest1
	-./cardtest1
	gcov -abcf dominion.c > coverc1.out
	cat dominion.c.gcov >> coverc1.out	
	rm -f *.gcov *.so

gcovcard2: cardtest2
	-./cardtest2
	gcov -abcf dominion.c > coverc2.out
	cat dominion.c.gcov >> coverc2.out
	rm -f *.gcov *.so

gcovcard3: cardtest3
	-./cardtest3 
	gcov -abcf dominion.c > coverc3.out
	cat dominion.c.gcov >> coverc3.out
	rm -f *.gcov *.so

gcovcard4: cardtest4
	-./cardtest4
	gcov -abcf dominion.c > coverc4.out
	cat dominion.c.gcov >> coverc4.out

coverage: gcovunit1 gcovunit2 gcovunit3 gcovunit4 gcovcard1 gcovcard2 gcovcard3 gcovcard4
	echo "/* ---------------UnitTest 1--------------------- */" > coverage1.txt
	cat coveru1.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------UnitTest 2--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coveru2.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------UnitTest 3--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coveru3.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------UnitTest 4--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coveru4.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------CardTest 1--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coverc1.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------CardTest 2--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coverc2.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------CardTest 3--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coverc3.out >> coverage1.txt
	echo " " >> coverage1.txt
	echo "/* ---------------CardTest 4--------------------- */" >> coverage1.txt
	echo " " >> coverage1.txt
	cat coverc4.out >> coverage1.txt

# ===========================================================================

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

# ===========================================================================

clean:
	rm -f *.o $(EXECS) playdom.exe test.exe player.exe testInit.exe 
	rm -f *.gcov *.gcda *.gcno *.so
	#rm -f cover*.out 