/*unittest3.c
This file will test the Shuffle function.  

The tests below will check the following aspects of the shuffle function:
1) The Shuffle function properly checks whether a player has cards to be shuffled
2) The Shuffle function properly shuffles the player's cards
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

    printf ("Begin testing of SHUFFLE function.\n");  
	
	int seed = 1234;
    int numPlayer = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
    /*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
	
	int shuffled_cards[10]; //Array to store post-shuffle cards
	 
	int i; //Loop driver variable
	int error = 0;  //Global error flag, used to report all tests passed
	
	
	for(i = 0; i < 10; i++) {
		//First, build deck of cards
	
		shuffled_cards[i] = Game_State->deck[0][i];
	}//End FOR
	
	Game_State->deckCount[0] = 0;  //Set deckCount for shuffle() function use
	
	/*The shuffle() function must check to see whether a given player has cards 
	to be shuffled.  The first test will check to see whether this determination 
	was made by evaluating the return value of the shuffle() function.*/
	
	if(shuffle(0, Game_State) != -1) {
		//Failed to check if player has more than 1 card
	
		printf("Check test failed, did not determine if player has cards to be shuffled.\n");
		error = -1;
		
	}//End IF
	
	else {  
		//Test passed, shuffle function appropriately checked
	
		printf("Check test passed, successful determination that player has  cards to be shuffled.\n");
	
	}//End ELSE
	
	
	Game_State->deckCount[0] = 10;  //Set deckCount for shuffle() function use
	
	/*Second, the shuffle() function must also successfully shuffle the 
	cards.  This test will check the return value of the shuffle function 
	to evaluate whether the cards were successfully shuffled*/
	
	if(shuffle(0, Game_State) < 0)
	{
		printf("Shuffle test failed, cards were not shuffled properly.\n");
		
		error = -1;
	}
	
	else {
		//Test passed, cards were successfully shuffled
		
		printf("Shuffle test passed, successfully shuffled player's cards.\n");
	
	}//End ELSE
	
	
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All Shuffle tests passed.\n");
	}//End IF
	
    printf ("End testing of SHUFFLE function.\n");
	
	return 0; 
}