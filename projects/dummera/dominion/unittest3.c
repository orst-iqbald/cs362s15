#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 1

int testDiscardCard(int m_handPos, int player, struct gameState *state, int flag)
{
  struct gameState pre;
        memcpy(&pre, state, sizeof(struct gameState));

  return discardCard(m_handPos, player, state, flag);
}

int main(int argc, char* argv[])
{
    printf("\n\n****Start Unit Test 3: DiscardCard****\n");
  struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
  int j;
    int players[NUM_PLAYERS];
  int playerHandCount[NUM_PLAYERS];
    int flag = 0;
  enum CARD m_supplyPos;
  
SelectStream(2);
  PutSeed(3);

    printf ("Start initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, m_state);
    printf("Pass\n");
  
  //create num of players and record their hand count
  for(i=0; i < NUM_PLAYERS; i++)
    {
        players[i] = i;
    playerHandCount[i] = m_state->handCount[i];
    }
  
  for(i=0; i < NUM_PLAYERS; i++)
  {
    for(j=playerHandCount[i] - 1; j >= 0; j--)
    {
      int m_handCount = m_state->handCount[i];
      int m_handPos = m_handCount - 1;
      int m_playedCount = m_state->playedCardCount;
      int Pass = 0;
      if(m_handCount % 2 == 0)
      {
        flag = 0;
      }
      else
        flag = 1;
      printf("Player %d testDiscardCard ", i+1);
      printf("flag:%d ", flag);
      printf("discard %d.....", m_handCount);
      if(testDiscardCard(m_handPos, players[i], m_state, flag) == 0)
      {
        if(flag == 0)
        {
          if(m_state->playedCardCount != m_playedCount + 1)
          {
            printf("FAIL - playedCardCount; ");
            Pass = 1;
          }
          if(m_state->playedCards[m_state->playedCardCount + 1] != m_state->hand[i][m_handPos])
          {
            printf("FAIL - playedCards; ");
            Pass = 1;
          }
        }
        if(m_handCount - 1 != m_state->handCount[i])
        {
          printf("FAIL - handCount; ");
          Pass = 1;
        }
        if(Pass != 0)
        {
          printf("\n");
        }
        else
        {
          printf("Pass\n");
        }
      }
    }
  }
    printf("****End of Unit Test 3****\n");
    return 0;
} 
