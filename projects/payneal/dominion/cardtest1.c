/* -----------------------------------------------------------------------
 * a card test for smithy() in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main() {
    
    int seed = 1000;
    int players = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState *play = newGame();
    
    int fails=0;
    int passes=0;
    
#if (NOISY_TEST == 1)
    printf ("TESTING Smithy Card():\n");
#endif
    
    
    //initialize new game
    int start = initializeGame(players, k, seed, play);
    
    //  no need to contine if this fails
    assert( start == 0);
    
    shuffle(0, play);
    
#if (NOISY_TEST == 1)
    printf("\nGame just initilized with %i players\n", players);
#endif
    
    int cardsinHand1 = play->handCount[0];
    int cardsinDeck1= play->deckCount[0];
    
#if (NOISY_TEST == 1)
    printf(" this is the number of cards in player ones hand %i\n", cardsinHand1);
    printf(" this is the number of cards in the players dekc %i\n", cardsinDeck1);
#endif
    
    //give player a smithy card
    play->hand[whoseTurn(play)][0] = smithy;
    int cat = cardSmithy(whoseTurn(play), play, 0);
    
    int cardsinHand2= play->handCount[0];
    int cardsinDeck2 = play->deckCount[0];
    
    printf(" smitty card was put in deck\n");
    printf("test cards in hand increased: ");
    if( cardsinHand2 > cardsinHand1)
    {
        passes++;
#if (NOISY_TEST == 1)
        printf("TRUE\n");
#endif
    }
    else
    {
        fails++;
#if (NOISY_TEST == 1)
        printf("FALSE\n");
#endif
    }
    
#if (NOISY_TEST == 1)
    printf("test cards in deck decressed: ");
#endif
    if( cardsinDeck1 > cardsinDeck2)
    {
        passes++;
#if (NOISY_TEST == 1)
        printf("TRUE\n");
#endif
    }
    else
    {
        fails++;
#if (NOISY_TEST == 1)
        printf("FALSE\n");
#endif
    }
    
    // known error
#if (NOISY_TEST == 1)
    printf("there is a difference of 2 with cardhs in hand: " );
#endif
    if (cardsinHand2 - cardsinHand1 ==2)
    {
        passes++;
#if (NOISY_TEST == 1)
        printf("TRUE\n");
#endif
    }
    else
    {
        fails++;
#if (NOISY_TEST == 1)
        printf("FALSE\n");
#endif
    }
    
#if (NOISY_TEST == 1)
    printf("there is a difference of 3 with cards in deck: " );
#endif
    if (cardsinHand2 - cardsinHand1 ==3)
    {
        passes++;
#if (NOISY_TEST == 1)
        printf("TRUE\n");
#endif
    }
    else
    {
        fails++;
#if (NOISY_TEST == 1)
        printf("FALSE\n");
#endif
    }
    
#if (NOISY_TEST == 1)
    printf(" this is the number of cards in player ones hand %i\n", cardsinHand2);
    printf(" this is the number of cards in the players dekc %i\n", cardsinDeck2);
#endif
    
#if (NOISY_TEST == 1)
    printf("the # of fails = %i\n", fails);
    printf("the # of passes = %i\n", passes);
#endif
    
    if (passes != 4)
    {
#if (NOISY_TEST == 1)
        printf(" Program Failed");
#endif
        
        return -1;
    }
    
#if (NOISY_TEST == 1)
    printf("Program Passed");
#endif
    
    return 0;
}
