/*randomtestcard.c
This file will randomly test the Village Card.  
In my implementation, the Village card function is named  
"int villageCard(int handPos, int currentPlayer, struct gameState *state)" 
and it is called by the "village" case within the cardEffect() function.  

The tests below will check the following aspects of the Village card:
1) The Village card properly adds 2 actions
2) The Village card does not change the total number of the player's cards

The testing is made random using a random system time-based seed and the 
rand() function in the following ways:
1) Random game initialization seed
2) Random number of players
3) Randomly selected test player

Instructions to run this program are contained in the accompanying makefile.  
Please run "make all" and then "make testrandomcard".
Output will be printed to the "randomtestcard.out" file.*/

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
	
	printf ("Begin random testing of VILLAGE card.\n");  
	
    /*Initial card set, includes Village card*/
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
	smithy, village, baron, great_hall};
	
	/*Tracking variables for game initialize/play as well as 
	pre- and post- comparison*/
    int treasure_start;
	int treasure_end;
	int treasure_count;
	int hand_count;
	int hand_count_start;
	int hand_count_end;
	int hand_position;  
	int seed;
	int seed_count;		
    int numPlayer;
	int test_player;
	int card_tracker;
	
	/*Number of random tests to run, initially set to 1 random test.  
	Increase this variable to run more tests.*/
	
	int test_number = 1;
	
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
	int action_count_start = 0;
	seed_count = 0;
	
	/*Create a new game state struct and initialize the game 
	for testing*/
	
    struct gameState *Game_State = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, cards, seed, Game_State);
    
	//Begin testing by selecting a player randomly
	
	test_player = (rand() % numPlayer);
	
	int i = 0; //Loop driver variable
	
	for(i = 0 ; i < test_number; i++){

		card_tracker = rand() % numPlayer;
	
		/*Randomly set maximum number of cards and apply to Game State.
		10 is the max number for this test.*/
		
		hand_count = rand() % 10;
		hand_position = hand_count;
	
		Game_State->handCount[card_tracker] = hand_count; 

		Game_State->whoseTurn = card_tracker;

		hand_count_start = Game_State->handCount[card_tracker];
		action_count_start = Game_State->numActions;
	
		/*Play Village card with random player and hand position*/
		
		villageCard(hand_position, card_tracker, Game_State);
		printf("Village card played.\n");

		/*The Village card should increase the total number of the selected 
		player's actions by two*/
		if(Game_State->numActions == action_count_start + 2){
		
			printf("Passed action count test.\n");
		}//End IF
		
		else{	//Otherwise, test failed
			printf("Failed test - ending action count not initial + 2\n");
		
		}//End ELSE
		
		/*However, the Village card should not increase the total number 
		of cards held by that player*/
		
		if(Game_State->handCount[card_tracker] == hand_count_start){
		
			printf("Passed hand count test.\n");
		}//End IF
		
		else{	//Otherwise, test failed
			
			printf("Failed test - ending hand card count not equal to initial\n");
		}//End ELSE
	
	}//End FOR
	
	printf("End random testing of VILLAGE card.\n");
	
return 0;
} //End main()
	
