/*randomtestadventurer.c
This file will randomly test the Adventurer card.  
In my implementation, the Adventurer card function is named  
"int adventurerCard(int currentPlayer, struct gameState *state)" 
and it is called by the  “adventurer” case within the cardEffect() function.  

The tests below will check the following aspects of the Adventurer card:
1) The Adventurer card properly adds 2 treasure cards to the player's hand
2) The Adventurer card properly increments the player's hand count

The testing is made random using a random system time-based seed and the 
rand() function in the following ways:
1) Random game initialization seed
2) Random number of players
3) Randomly selected test player

Instructions to run this program are contained in the accompanying makefile.  
Please run "make all" and then "make testrandomadventurer".
Output will be printed to the "randomtestadventurer.out" file.*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include "interface.h"
#include <math.h>
#include <assert.h>

int main() {

    /*Set seed for the random() function based on the system
	time, to improve randomness*/
	
	srand(time(NULL));  
	
	printf ("Begin random testing of ADVENTURER card.\n");  
	
    /*Initial card set, includes Adventurer card*/
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
	/*Tracking variables for game initialize/play as well as 
	pre- and post- comparison*/
    int treasure_start;
	int treasure_end;
	int treasure_count;
	int hand_count_start;
	int hand_count_end;
	int hand_position;  
	int seed;
	int seed_count;		
    int numPlayer;
	int test_player;
	
	/*Set up random game variables */
	
	seed = (rand() % 99999);  //Random seed between 0 and 99999
	
	numPlayer = ((rand() % 3) + 2);  
			//Select a random number of players between 2 and 4
	
	
	/*Remaining game variables set to zero*/
	
	treasure_start = 0;
	treasure_end = 0;
	treasure_count = 0;
	hand_count_start = 0;
	hand_count_end = 0;
	seed_count = 0;
	
	
	/*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
    
	//Begin testing by selecting a player randomly
	
	test_player = (rand() % numPlayer);
	
	/*Assess cards for treasure prior to playing Adventurer card.  
	Will do same assessment after card is played*/
	
	int i = 0; //Loop driver variable
	
	for(i = 0; i < Game_State->handCount[test_player]; i++){
	
		/*Check each card to determine whether it is treasure.  
		If so, increment treasure_start.*/
		if(Game_State->hand[test_player][i] == gold || Game_State->hand[test_player][i] == silver || Game_State->hand[test_player][i] == copper){

			treasure_start++;

			if(Game_State->hand[test_player][i] == copper && i == 0){
				Game_State->hand[test_player][i] = gold;
			}//End IF
		
		}//End IF
		
		else {	//Not a treasure card, advance hand 
			hand_position = i;
		}//End ELSE

		hand_count_start = i + 1;  
				//End of loop, increment initial hand count
	
	}//End FOR
	
	
	/*Output statements to for tester, present player and initial 
	pre-test conditions*/

	printf("Tested game parameters:\n");
	printf("Players = %d\n", numPlayer);
	printf("Random player drawn for = %d\n", test_player);
	printf("Random player deck count = %d\n", Game_State->deckCount[test_player]);
	
	printf("Initial treasure cards: %d\n", treasure_start);
	printf("Initial player hand: = %d\n", hand_count_start);
	
	/*Call adventurerCard() for test_player and this game state*/
	
	adventurerCard(test_player, Game_State); 
	
	for(i = 0; i < Game_State->handCount[test_player];i++){
	
		if(Game_State->hand[test_player][i] == gold || Game_State->hand[test_player][i] == silver || Game_State->hand[test_player][i] == copper){

			treasure_end++;
			hand_count_end = i + 1;
		}//End IF
		
	}//End FOR
	
	printf("Adventurer card played.\n");
	printf("Ending treasure cards: %d\n", treasure_end);
	printf("Ending player hand: = %d\n", hand_count_end);
	
	/*The Adventurer card should add 2 treasure card to any player's
	hand.  Accordingly, the following test will check if that 
	has properly occurred.*/
	
	if((treasure_start + 2) != treasure_end){

		printf("Failed test - ending treasure card count not initial + 2\n");
		
		seed_count++;
	}//End IF
	
	else {	//Otherwise, 2 treasure cards added successfully and test passed
	
		printf("Treasure card addition test passed\n");
	
	}//End ELSE

	/*Similarly, the player's hand count should increase by 2.  
	The following test will check if that has properly occurred.*/
	
	if((hand_count_start + 2) != hand_count_end){

		printf("Failed test - ending hand count not initial + 2\n");
		
	}//End IF
	
	else {	//Otherwise, 2 cards added successfully and test passed
	
		printf("Hand count addition test passed\n");
	
	}//End ELSE

	printf ("End random testing of ADVENTURER card.\n");

return 0;
}//End main()