#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkVillage(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	int card, choice1, choice2, choice3, handPos;
	card = village;
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	int* bonus;
	*bonus = 0;
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
}
