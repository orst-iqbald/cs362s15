gcc -o binsearch binsearch.c -coverage -fpic -lm

binsearch

gcov binsearch.c

gcov binsearch.c -b

gcov compare.c bst.c main.c