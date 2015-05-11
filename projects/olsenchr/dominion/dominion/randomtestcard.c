#include <stdio.h>
#include "dominion.c"
#include "rngs.c"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

extern const char* __progname;

void checkSteward(struct gameState* state, int currentPlayer, int choice1, int choice2, int choice3, int handPos);

int main(){
	int i,j; // counters
	struct gameState* G = malloc(sizeof(struct gameState)); //create gamestate
	int currentPlayer, choice1, choice2, choice3, handPos; //params for steward cal
	int r = time(NULL); //init random seed

	printf("Testing steward\n");
	printf("RANDOM TESTS\n");
	for(i=0; i<1000000; i++){
		srand(r+i); //use counter to get new random number for each test
		//Randomize player
		currentPlayer = floor(rand()%2);
		//Randomize deck count
		G->deckCount[currentPlayer] = floor(rand() % MAX_DECK);
		//Randomize discard count
		G->discardCount[currentPlayer] =  floor(rand() % MAX_DECK);
		//Randomize hand count
		G->handCount[currentPlayer] = floor(rand() % MAX_HAND);
		//Randomize cards in hand
		for (j=0;j<G->handCount[currentPlayer];j++){
			G->hand[currentPlayer][j] = floor(rand() % 27);
		}
		//Make sure there are cards in deck and discard
		if(G->deckCount[currentPlayer] < 2 || G->discardCount[currentPlayer] < 2){
			j = floor(rand()%2);
			if(j==1){
				G->deckCount[currentPlayer] = floor((rand() % MAX_DECK -2) + 2);
			}else{
				G->discardCount[currentPlayer] = floor((rand() % MAX_DECK - 2) + 2);
			}
		}
		//Make sure player has a hand
		if(G->handCount[currentPlayer] == 0){
			G->handCount[currentPlayer] = floor(rand() % (MAX_HAND - 1)) + 1;			
		}
		//Randomize cards in deck
		for(j=0;j<G->deckCount[currentPlayer];j++){
			G->deck[currentPlayer][j] = floor(rand()%27);
		}
		//Randomize cards in discard
		for(j=0;j<G->discardCount[currentPlayer];j++){
			G->discard[currentPlayer][j] = floor(rand()%27);
		}
		//randomize choices
		choice1 = floor(rand() % G->handCount[currentPlayer]);
		choice2 = floor(rand() % G->handCount[currentPlayer]);
		choice3 = floor(rand() % G->handCount[currentPlayer]);
		//randomize handpos
		handPos = floor(rand() % G->handCount[currentPlayer]);
		checkSteward(G,currentPlayer,choice1,choice2,choice3,handPos);
		//printf("ended run %d\n", i); //debug trace
	}

	printf("Tests passed\n");
	return 0;
}

void checkSteward(struct gameState* state, int currentPlayer, int choice1, int choice2, int choice3, int handPos){
	int res = 0, cards = 0, coins = 0;
	char dbx[255];
	//Pass conditions
	if(choice1 == 1){
		cards = state->handCount[currentPlayer] + 1;
		coins = state->coins;
	}
	else if(choice1 == 2){
		coins = state->coins + 2;
		cards = state->handCount[currentPlayer];
	}
	else{
		cards = state->handCount[currentPlayer] - 3;
		coins = state->coins;
	}
	res = playSteward(state,currentPlayer,choice1,choice2,choice3,handPos);
	//FAILURE CONDITIONS
	if(cards != state->handCount[currentPlayer]){
		printf("TEST FAILED: Invalid card number\n");
		printf("Cards = %d\n\n", state->handCount[currentPlayer]);
		//Use gdb to dump struct contents
		/********************************
		See here for code source!
		http://stackoverflow.com/questions/3311182/linux-c-easy-pretty-dump-p    rintout-of-structs-like-in-gdb-from-source-co
		*******************************/
		sprintf(dbx, "echo 'p (struct %s)*%p\n' > gdbcmds", "gameState", state);
		system(dbx);
		sprintf(dbx, "echo 'where\ndetach' | gdb -batch --command=gdbcmds %s %d > struct.dump", __progname, getpid() );
		system(dbx);
		sprintf(dbx, "cat struct.dump");
		system(dbx);
	}
	if(coins != state->coins){
		printf("TEST FAILED: Invalid coin count\n");
		printf("Coins = %d\n\n", state->handCount[currentPlayer]);
		sprintf(dbx, "echo 'p (struct %s)*%p\n' > gdbcmds", "gameState", state);
		system(dbx);
		sprintf(dbx, "echo 'where\ndetach' | gdb -batch --command=gdbcmds %s %d > struct.dump", __progname, getpid() );
		system(dbx);
		sprintf(dbx, "cat struct.dump");
		system(dbx);
	}
	
	return;
}
