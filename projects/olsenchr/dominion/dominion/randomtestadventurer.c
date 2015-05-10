#include <stdio.h>
#include "dominion.c"
#include "rngs.c"
#include <math.h>
#include <stdlib.h>
#include <time.h>

extern const char* __progname;

void checkAdventurer(struct gameState *G, int cur, int* tmp, int d, int c, int z);

int main(){
	int i, j; //counters
	int passed = 0; //number of passed tests
	int p = 0; // player
	int tmp[MAX_HAND]; //temp hand for adventurer
	int d = 0; //
	int c = 0; // params for adventurer call
	int z = 0; //
	int r = time(NULL); //initialize random seed
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; //kingdom cards
	struct gameState *G = malloc(sizeof(struct gameState)); //create gamestate
	
	printf("Testing adventurer\n");

	printf("RANDOM TESTS\n");
	for(i=0; i<1000000;i++){
		srand(r + i); //Because tests finish so quickly, 
						  //time(NULL) won't change the rand() value 
						  //so we also use the counter
		//Randomize player
		p = floor((rand()%2));
		//Randomize deck count
		G->deckCount[p] = floor(rand() % MAX_DECK);
		//Randomize discard count
		G->discardCount[p] = floor(rand() % MAX_DECK);
		//Make sure player possesses at least two treasure cards
		//Otherwise, test will loop infinitely
		G->handCount[currentPlayer] = floor(rand() % MAX_HAND);
		if(G->deckCount[p] < 2 || G->discardCount[p] < 2){
			j = floor(rand()%2);
			if(j == 1){
				G->deckCount[p] = floor((rand() % MAX_DECK - 2) + 2);
			}else{
				G->discardCount[p] = floor((rand() % MAX_DECK - 2) + 2);
			}
		}
		//Randomize cards in deck
		for(j=0;j<G->deckCount[p];j++){
			G->deck[p][j] = floor(rand()%28);
		}
		//Randomize cards in discard
		for(j=0;j<G->discardCount[p];j++){
			G->discard[p][j] = floor(rand()%28);
		}
		//Make sure player has a hand
		if(G->handCount[currentPlayer] == 0){
			G->handCount[currentPlayer] = floor(rand() % (MAX_HAND - 1)) + 1;        }  
		checkAdventurer(G, p, tmp, d, c, z);
	}
	return 0;
}

void checkAdventurer(struct gameState *G, int cur, int* tmp, int d, int c, int z){
	int p,i,treasure = 0;
	char dbx[255];
	p = G->whoseTurn;
	playAdventurer(G, cur, tmp, d, c, z);
	//Check that player has at least two treasures in hand
	for(i=0;i<G->handCount[p];i++){
		if(G->hand[p][i] == copper || G->hand[p][i] == silver || G->hand[p][i] == gold){
			treasure++;
		}
	}
	//FAILURE CASE
	if(treasure < 2){
		printf("TEST FAILED: \n");
		printf("Player: %d\n", p);
		printf("Deck size: %d\n", G->deckCount[p]);
		printf("Discard size: %d\n\n", G->discardCount[p]);
		//Use gdb to dump struct contents
		/********************************
		 See here for code source!
		 http://stackoverflow.com/questions/3311182/linux-c-easy-pretty-dump-printout-of-structs-like-in-gdb-from-source-co
		 *******************************/
		sprintf(dbx, "echo 'p (struct %s)*%p\n' > gdbcmds", "gameState", state    );
		system(dbx);
		sprintf(dbx, "echo 'where\ndetach' | gdb -batch --command=gdbcmds %s %    d > struct.dump", __progname, getpid() );
		system(dbx);
		sprintf(dbx, "cat struct.dump");
		system(dbx);
	}
}
