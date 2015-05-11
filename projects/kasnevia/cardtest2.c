/*cardtest2.c
This file will test the Smithy card.  In my implementation, the 
Smithy card function is named  
"int smithyCard(int handPos, int currentPlayer, struct gameState *state)" 
and it is called by the  “smithy” case within the cardEffect() function.  

The tests below will check the following aspects of the Smithy card:
1) The player gains two cards after playing the Smithy card
2) The Smithy card is properly discarded after being played
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    printf ("Begin testing of SMITHY card.\n");  
	
	int seed = 1234;
    int numPlayer = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};

    /*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
    
	Game_State->hand[0][0] = smithy;  //Give player the Smithy card
    int player_hand = 0;
	int error = 0;  //Global error flag, used to report all tests passed

    /*According to the rules of the game, with the Smithy card a player 
	draws three cards and adds them to his or her hand.  The Smithy card 
	contains only this action, so it is discarded once used.*/  
    
    player_hand = Game_State->handCount[0];
		//Store pre-Smithy player hand to allow for comparison later

  	smithyCard(0,0, Game_State);
		//Call smithyCard() based on current Game_State, for Player 0 and hand position 0

	if(Game_State->handCount[0] == player_hand + 2) {
		/*IF statement to test that the player gained a total of 2 cards from playing Smith card.  That is, receiving 3 cards and discarding the Smithy card mean a net gain of two cards.*/
	
        printf("Player hand gained 2 cards.  Hand count test OK.\n");
    }//End IF
	
    else {
		/*If any result other than player_hand + 2, Smithy card function erred and therefore this test fails.*/
		
        printf("Hand count test failed, player gained improper number of cards.\n");
		
		error = -1;

	}//End ELSE
	
	/*The Smithy card should be discarded (added to the discard pile) after it is played.  This test will check the discard pile to see whether the 
	Smithy card appears as the last card in that pile (meaning it was the most recently discarded).*/
	
	if(Game_State->playedCards[Game_State->playedCardCount - 1] == smithy) {
		
		printf("Smithy card discarded.  Discard test OK.\n");
		
	}//End IF
	
	else {
		/*If any result other than the Smithy card, card was not properly 
		discarded and therefore this test fails.*/
		
        printf("Discard test failed, Smithy not most recent card on discard pile.\n");
		
		error = -1;

	}//End ELSE
	
		
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
	
		printf("All Smithy tests passed.\n");
		
	}//End IF
	
    printf ("End testing of SMITHY card.\n");
	
	return 0; 
}