CFLAGS = -Wall -g -fpic -coverage -lm -std=c99
FILES = ~/Documents/School/Spring2015/CS362/cs362s15/projects/currymi/dominion/
UNITTESTS = unitTests/unittest1.c unitTests/unittest2.c unitTests/unittest3.c unitTests/unittest4.c
CARDTESTS = cardTests/cardTest1.c cardTests/cardTest2.c cardTest/cardTest3.c cardTest/cardTest4.c


unitTest:


	echo "Unit Tests" >> tests.out
	echo "==========" >> tests.out
	echo "" >> tests.out
	echo "unittest1.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/unittest1.c ../dominion.c ../rngs.c -o unittest1  $(CFLAGS) -I $(FILES)
	./unittest1 >> tests.out
	gcov unitTest/unittest2.c >> tests.out

	echo "" >> tests.out
	echo "unittest2.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/unittest2.c ../dominion.c ../rngs.c -o unittest2  $(CFLAGS) -I $(FILES)
	./unittest2 >> tests.out
	gcov unittest2 >> tests.out


	echo "" >> tests.out
	echo "unittest3.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/unittest3.c ../dominion.c ../rngs.c -o unittest3  $(CFLAGS) -I $(FILES)
	./unittest3 >> tests.out
	gcov unittest3 >> tests.out

	echo "" >> tests.out
	echo "unittest4.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/unittest4.c ../dominion.c ../rngs.c -o unittest4  $(CFLAGS) -I $(FILES)
	./unittest4 >> tests.out
	gcov unittest4 >> tests.out

cardTests: unitTests/cardTest1.c unitTests/cardTest2.c unitTests/cardTest3.c unitTests/cardTest4.c

	echo "" >> tests.out
	echo "cardTest1.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/cardTest1.c ../dominion.c ../rngs.c -o cardTest1 $(CFLAGS) -I $(FILES)
	./cardTest1 >> tests.out
	gcov cardTest1 >> tests.out

	echo "" >> tests.out
	echo "cardTest2.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/cardTest2.c ../dominion.c ../rngs.c -o cardTest2 $(CFLAGS) -I $(FILES)

	echo "" >> tests.out
	echo "cardTest3.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/cardTest3.c ../dominion.c ../rngs.c -o cardTest3 $(CFLAGS) -I $(FILES)
	./cardTest3 >> tests.out
	gcov cardTest3 >> tests.out

	echo "" >> tests.out
	echo "cardTest4.c:" >> tests.out
	echo "------------" >> tests.out
	gcc unitTests/cardTest4.c ../dominion.c ../rngs.c -o cardTest4 $(CFLAGS) -I $(FILES)
	./cardTest4 >> tests.out
	gcov cardTest4 >> tests.out

clean:
	rm tests.out

cleanall: 
	rm tests.out unittest1 unittest2 unittest3 unittest4 unittest5 *.gcda *.gcno *.gcov cardTest1 cardTest2 cardTest3 cardTest
