CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: randomtestadventurer.out randomtestcard.out 

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o interface.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o  interface.o
	echo "randomtestadventurer:" > randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	echo " " >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	
randomtestcard.out: randomtestcard.c dominion.o rngs.o  interface.o
	echo "randomtestcard.c:" > randomtestcard.out
	gcc -o randomtestcard randomtestcard.c dominion.o rngs.o interface.o $(CFLAGS)
	randomtestcard >> randomtestcard.out
	echo " " >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out

cleanall: 
	rm *.out  *.gcda *.gcno *.gcov *.o
	rm randomtestadventurer randomtestcard