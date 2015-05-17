#include "dominion.h" 
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include "interface.h"

//Random Test for Adventurer

int main() {
	int i, j, p, r;
	int card_num, adpos;
	int temp_coins;
	int temp_handcount;
	struct gameState gs;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, treasure_map, tribute, smithy};
	srand(time(NULL));
	char *str=malloc(sizeof(char)*30);

	printf("\nTest Adventurer\n");

	for(j = 0; j < 100; j++){
		r = initializeGame(4, k, 200, &gs);
		assert(r == 0);

		printf("\n=============== Iteration # %d ===============\n", (j + 1));

		for(p = 0; p < 4; p++){
			gs.hand[p][gs.handCount[p]] = adventurer;
			gs.handCount[p]++;
			gs.deckCount[p] = 0;
			for(i = 0; i < 21; i++){//Add 20 random cards to deck
				gs.deck[p][i] = (rand() % 27);
				gs.deckCount[p]++;
			}
			printf("\n--------------Before Adventurer--------------\n");
			printf("Player # %d\n", (p + 1));
			printf("Actions: %d\n", gs.numActions);
			printf("Coins: %d\n", gs.coins);
			temp_coins=gs.coins;
			printf("Hand Count: %d\n", gs.handCount[p]);
			temp_handcount=gs.handCount[p];
			printf("Treasures in Deck:\n");
			for(i = 0; i < gs.deckCount[p]; i++){
				card_num = gs.deck[p][i];
				if((card_num == silver) || (card_num == gold) || (card_num == copper)){
					cardNumToName(card_num,str);
					printf("%s",str);
					printf("\n");
				}
			}
			printf("\n");
			for(i = 0; i < gs.handCount[p]; i++){
				card_num = gs.hand[p][i];
				printf("Hand # %d is ", i+1);
				cardNumToName(card_num,str);
				printf("%s",str);
				printf("\n");
				if(handCard(i, &gs) == adventurer){
					adpos = i;
				}
		}

		playCard(adpos, 0, 0, 0, &gs);

		printf("--------------After Adventurer--------------\n");
		printf("Player # %d\n", (p + 1));
		printf("Actions: %d\n", gs.numActions);
		printf("Coins: %d, ", gs.coins);
		if (temp_coins+2==gs.coins)
			printf("which is expected\n");
		else 
			printf("which is NOT expected\n");
		printf("Hand Count: %d, ", gs.handCount[p]);
		if (temp_handcount+2==gs.handCount[p])
			printf("which is expected\n");
		else 
			printf("which is NOT expected\n");
		for(i = 0; i < gs.handCount[p]; i++){
			card_num = gs.hand[p][i];
			printf("Hand # %d is ", i+1);
			cardNumToName(card_num,str);
			printf("%s",str);
			printf("\n");
		}

		endTurn(&gs);
		}
	}
	printf("\n=============================================\n");
	return 0;
}

