/*cardtest1.c
This file will test the Adventurer card.  In my implementation, the 
Adventurer card function is named  
"int adventurerCard(int currentPlayer, struct gameState *state)" 
and it is called by the  “adventurer” case within the cardEffect() function.  

The tests below will check the following aspects of the Adventurer card:
1) The Adventurer card properly adds treasure cards to the player's hand
2) The Adventurer card is properly discarded after being played
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    printf ("Begin testing of ADVENTURER card.\n");  
	
	int seed = 1234;
    int numPlayer = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
    /*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
    
	Game_State->hand[0][0] = adventurer;  //Give player the Adventurer card
    int player_hand = 0;
	int player_hand_count = 0; 
	int treasure_count = 0;  //Variable to monitor number of treasure cards
	int i; //Loop driver variable
	int error = 0;  //Global error flag, used to report all tests passed
	
	for(i = 0; i < Game_State->handCount[whoseTurn(Game_State)]; ++i) {
		/*Search player's hand to determine and count treasure cards*/
	
		player_hand = Game_State->hand[whoseTurn(Game_State)][i];  //Set to current card
	
		if(player_hand == gold || player_hand == silver || player_hand == copper) {
			/*Increment treasure_count to reflect existing treasure cards*/
			++treasure_count;
			
		}//End IF
	}//End FOR

	player_hand_count = Game_State->handCount[whoseTurn(Game_State)];  //Reset player's hand count

	adventurerCard(0, Game_State); 
		//Call adventurerCard() for player 0 and this game state
	
	for(i = 0; i < Game_State->handCount[whoseTurn(Game_State)]; ++i){
		/*Searching hand to update treasure_count  based on number of treasure 
		cards in new hand*/

		player_hand = Game_State->hand[whoseTurn(Game_State)][i];  //Set to current card
		
		if(player_hand == copper || player_hand == silver || player_hand == gold){
			/*Decrement treasure_count to reflect existing treasure cards*/
			--treasure_count;
		
		}//End IF
	}//End FOR
	
	if(treasure_count != -2) {
		/*This test will check to see whether the treasure cards gained by 
		the Adventurer card were correctly added to the player's hand.*/
	
		printf("Increment hand test failed, cards not properly added to player's hand\n");
		error = -1;
	}
	/*The Adventurer card should be discarded (added to the discard pile) after it is played.  This test will check the discard pile to see whether the 
	Adventurer card appears as the last card in that pile (meaning it was the most recently discarded).*/
	
	if(Game_State->playedCards[Game_State->playedCardCount - 1] == adventurer) {
		
		printf("Adventurer card discarded.  Discard test OK.\n");
		
	}//End IF
	
	else {
		/*If any result other than the Adventurer card, card was not properly 
		discarded and therefore this test fails.*/
		
        printf("Discard test failed, Adventurer not most recent card on discard pile.\n");
		
		error = -1;

	}//End ELSE

	
	if(error != -1) {
		/*If nothing has triggered the error flag, all tests have passed.*/
		
		printf("All Adventurer tests passed.\n");
	}//End IF
	
    printf ("End testing of ADVENTURER card.\n");
	
	return 0; 
}