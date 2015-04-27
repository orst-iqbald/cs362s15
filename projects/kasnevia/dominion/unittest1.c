/*unittest1.c
This file will test the supplyCount function.  

The tests below will check the following aspects of the supplyCount function:
1) The initial 


Whether getCost returns the correct values of given cards
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main() {

    printf ("Begin testing of SUPPLYCOUNT function.\n");  
	
	int seed = 1234;
    int numPlayer = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
	/*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
	 
	int i; //Loop driver variable
	int error = 0;  //Global error flag, used to report all tests passed
	
	/*This test will loop over the cards[] array and test the number of 
	each card against the value returned by supplyCount.  	
	This test was adapted from the examples posted by the instructor.*/
	
    for(i = 0; i < 10; i++) {
	
    	Game_State->supplyCount[cards[i]] = i; 
			//Run supplyCount for each card in cards[] array
    
		if(supplyCount(cards[i], Game_State) != i) {
			//Compare supplyCount values
	
    		printf("Value check failed, supplyCount did not return the correct value");
			error = -1;
    	
		}//End IF
		
    }//End FOR

	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All SupplyCount tests passed.\n");
	}//End IF
	
	if(error == -1){
		printf("Supply value retrieval test failed, SupplyCount did not return the correct count.\n");
	
	}//End IF
	
    printf ("End testing of SUPPLYCOUNT function.\n");
	
	return 0; 
}