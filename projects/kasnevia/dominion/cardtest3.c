/*cardtest3.c
This file will test the Village card.  In my implementation, the 
Village card function is named  
"int villageCard(int handPos, int currentPlayer, struct gameState *state)" 
and it is called by the "village" case within the cardEffect() function.  

The tests below will check the following aspects of the Village card:
1) The Village card properly adds 2 actions
2) The Village card does not change the total number of the player's cards
3) The Village card is properly discarded after being played
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

    printf ("Begin testing of VILLAGE card.\n");  
	
	int seed = 1234;
    int numPlayer = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
    /*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
    
	Game_State->hand[0][0] = adventurer;  //Give player 0 the Adventurer card
    int player_hand = 0;
	int player_hand_count = 0; 
	int cards_initial = 0;  //Counting variables for before/after cards
	int cards_final = 0; 
	int actions_initial = 0;  //Counting variables for before/after action cards
	int actions_final = 0; 
	int i; //Loop driver variable
	int error = 0;  //Global error flag, used to report all tests passed
	
	/*According to the game rules, the Village card gives the player the 
	ability to generate +2 or more actions.  This test will check whether 
	the number of actions have increased by 2 and the total number of 
	cards remain the same.*/
	
	cards_initial = Game_State->numActions;  
	actions_initial = Game_State->handCount[0];
		//Set initial action and card counts for comparison later
	
	villageCard(0, 0, Game_State);  //Run villageCard() function
	
	cards_final = Game_State->numActions;  //Set final action and card counts
	actions_final = Game_State->handCount[0];

	/*Comparison tests between initial and final actions and cards.  
	First test will check to see that the total number of cards have 
	not increased since the Village card was played.*/
	
	if (cards_final == cards_initial){
		printf("Cards test passed, number of cards before and after are the same.\n");
		error = -1;
	
	}//End IF
	
	else{  
		//Any other result means villageCard() was not run correctly
	
		printf("Cards test failed, player has a different number of cards after playing Village card.\n");
		
		error = -1;
	}//End IF
	
	/*Second test will check whether the number of actions have increased 
	by two.*/
	
	if (actions_final == actions_initial + 2){
		printf("Action increment test passed, final actions are two more than initial.\n");
		error = -1;
	
	}//End IF
	
	else{  
		//Any other result means villageCard() was not run correctly
	
		printf("Action increment test failed, final actions not properly incremented.\n");
		
		error = -1;
	}//End IF
	
	
	/*The Village card should be discarded (added to the discard pile) after it is played.  This test will check the discard pile to see whether the 
	Village card appears as the last card in that pile (meaning it was the most recently discarded).*/
	
	if(Game_State->playedCards[Game_State->playedCardCount - 1] == village) {
		
		printf("Village card discarded.  Discard test OK.\n");
		
	}//End IF
	
	else {
		/*If any result other than the Village card, card was not properly 
		discarded and therefore this test fails.*/
		
        printf("Discard test failed, Village not most recent card on discard pile.\n");
		
		error = -1;

	}//End ELSE

	
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All Village tests passed.\n");
	}//End IF
	
    printf ("End testing of VILLAGE card.\n");
	
	return 0; 
}