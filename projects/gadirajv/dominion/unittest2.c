/* -----------------------------------------------------------------------
	Unit test for the function: 
	struct gameState* newGame();
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	unittest2: unittest2.c dominion.o
		gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- 
 */
#include <stdio.h>
#include "dominion.h"
/* To suppress noise set this to 0 */
#define NOISY_TEST 1
/** test the function newGame */
void unittest2() {
	struct gameState* g = NULL;
	
	g = newGame();
	
	if (g == NULL) {
		printf("The function newGame failed \n");
	} else {
		printf("The function newGame successfully created gameState object. \n");
	}
	free(g);
	return;
}

int main() {
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	unittest2();
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	
	return 0;
}