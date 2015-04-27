/*unittest4.c
This file will test the kingdomCards function.  

The tests below will check the following aspects of the kingdomCards function:
1) Whether the kingdomCards function adds the correct cards to the deck
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

    printf ("Begin testing of KINGDOMCARDS function.\n");  
	
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
	int *function_cards;  //Pointer to store kingdomCards return values
	
	/*Begin by call the kingdomCards() function and storing the return values 
	in function_cards variable for comparison later.  Adding same cards as in 
	cards[] above*/
	
	function_cards = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	
	/*The kingdomCards function should add the same cards to the deck as 
	saved in the cards[] array.  This test will check whether that happened*/

	
	for(i = 0; i < 10; i++) {
	
		if(function_cards[i] != cards[i]){
				
			printf("Add test failed, did not add correct cards to player's deck.\n");
			error = -1;
				
		}//End IF
	}//End FOR
	
	
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All KingdomCards tests passed.\n");
	}//End IF
	
    printf ("End testing of KINGDOMCARDS function.\n");
	
	return 0; 
}