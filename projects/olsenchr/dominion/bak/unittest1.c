/*****************************
 * Unit Test for getCost()
 ****************************/

//There's no try/catch in C, so
//I'm assuming input is integer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	int seed = 100;
	int p;
	struct gameState G;
	
	printf("Testing getCost...\n");

	//test all values in cards enum against -1
	for( i = 0; i <= 26; i++){
		p = getCost(i);
		assert (p != -1);
	}
	printf("Passed test 1\n");

	//Test out of bounds value
	i = 27;
	p = getCost(i);
	assert (p == -1);
	printf("Passed test 2\n");

	i = -1;
	p = getCost(i);
	assert (p == -1);
	printf("Passed test 3\n");

	return 0;
}
