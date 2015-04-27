/*unittest2.c
This file will test the getCost function.  

The tests below will check the following aspects of the getCost function:
1) Whether getCost returns the correct values of given cards
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

    printf ("Begin testing of GETCOST function.\n");  
	
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
	
	/*In order to test getCost, set up an array of cards and a corresponding 
	array of cost values for those cards.*/
	
	char *card_names[10] = {"smithy", "village", "duchy", "province", "copper", "silver", "gold", "adventurer", "great_hall", "gardens"};
	
	int card_cost[10] = {4,3,5,8,0,3,6,6,3,4};

	/*The following code was adapted from the example dominion tests posted by the instructor.  
	This code will compare the cost of each card as retrieved by getCost to the values saved in the card_cost array.*/
	
	for(i = 0; i < 10; i++) {
	
		if(getCost(i) != card_cost[i]){
				
			//Cost retrieval test failed, getCost did not return the correct cost value
			error = -1;
				
		}//End IF
		
	}//End FOR
	
	
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All GetCost tests passed.\n");
	}//End IF
	
	if(error == -1){
		printf("Cost retrieval test failed, getCost did not return the correct cost value.\n");
	
	}//End IF
	
    printf ("End testing of GETCOST function.\n");
	
	return 0; 
}