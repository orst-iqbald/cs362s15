/* -----------------------------------------------------------------------
	Unit test for the function: 
	int compare(const void* a, const void* b);
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	unittest1: unittest1.c dominion.o
		gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- 
 */
 
#include <stdio.h>
#include "dominion.h"

/* To suppress noise set this to 0 */
#define NOISY_TEST 1

/** test compare */
void unittest1() {
	int a = 25;
	int b = 20;
	int result; /* selecting a value that is not 1 or -1 or 0 */
	
	result = compare(&a, &b);
	if (result != 1) {
		printf("The function Compare failed for a > b.  Test FAILED. \n");
	} else {
		printf("The function Compare Passed for a > b.  Test PASSED. \n");
	}
	result = compare(&b, &a);
	if (result != -1) {
		printf("The function Compare failed for a < b.  Test FAILED. \n");
	} else {
		printf("The function Compare passed  for a < b.  Test PASSED. \n");
	}
	result = compare(&a, &a);
	if (result != 0) {
		printf("The function Compare failed for a == a.  Test FAILED. \n");
	} else {
		printf("The function Compare passed for a == a.  Test PASSED. \n");
	}
	
	return;
}

int main() {
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	unittest1();
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	
	return 0;
}