//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              unittest2.c

/*Description: This is a unit test to test the getWinners() in dominion.c.
Each player will randomly be assign decks, discards, and hands. Also the
amount of players will also be determined randomly. This test will get the
score for each play, find the highscore, and find winner for each game. 
Then it will call the getWinners function to test.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTING 0

int testGetWinners(int players[MAX_PLAYERS], struct gameState *after)
{
  int i;
  int j;
  int highScore;
  int currentPlayer;
  int playerIdx;
  int beforeOut;
  int afterOut;
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));

  //this is getting score for each player
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    if (i >= before.numPlayers)
    {
      players[i] = -9999;
    }
    else
    {
      players[i] = scoreFor(i, &before);
    }
  }

  //this is to find highScore
  j = 0;
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    if (players[i] > players[j])
    {
      j = i;
    }
  }
  highScore = players[j];

  //this is adding 1 to players who had less turns
  currentPlayer = whoseTurn(&before);
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    if ( players[i] == highScore && i > currentPlayer )
    {
      players[i]++;
    }
  }

  //this is to find new highScore
  j = 0;
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    if ( players[i] > players[j] )
    {
      j = i;
    }
  }
  highScore = players[j];

  //this is to insert winners in array to 1 and losers to 0
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    //player that has highScore
    if ( players[i] == highScore )
    {
      //then player gets a 1 for win
      players[i] = 1;
    }
    else
    {
      //else they get a 0 for lose
      players[i] = 0;
    }
  }

  //loop through all players and find winner
  for(playerIdx = 0; playerIdx < before.numPlayers; playerIdx++)
  {
    if (players[playerIdx] == 1)
    {
      if(TESTING) printf("Player %d\n", playerIdx);
      {
        beforeOut = playerIdx;
      }
    }
  }

  //loop through all players and reset
  for(playerIdx = 0; playerIdx < before.numPlayers; playerIdx++)
  {
    players[playerIdx] = 0;
  }

  //this is the call to getWinners function to find winners in the after struct
  getWinners(players, after);

  for(playerIdx = 0; playerIdx < before.numPlayers; playerIdx++)
  {
    if (players[playerIdx] == 1)
    {
      if(TESTING) printf("Player %d\n", playerIdx);
      {
        afterOut = playerIdx;
      }
    }
  }
  
  if (beforeOut != afterOut) 
  {
    printf("getWinners() Failed Test\n");
    printf("getWinners() Not Calculating Winners Properly!\n");
  }
  
  assert(memcmp(&before, after, sizeof(struct gameState)) == 0);
  return 0;
}

int main()
{
  int i;
  int n;
  int j;
  int gameIterations = 2000; //change for the number of test games
  int players[MAX_PLAYERS];
  struct gameState testGame;

  //display testing message for unittest2
  printf ("----------------------------------------\n");
  printf ("FUNCTION getWinners() BEING TESTED...\n");
  printf ("RANDOM TESTS...\n");

  //this is initializing stream for random number generation
  SelectStream(2);
  PutSeed(3);

  //testing for 2000 iterations
  for(n = 0; n < gameIterations; n++)
  {
    for(i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&testGame)[i] = floor(Random() * 256);
    }

    int numPlayers = 0;

    //making sure to find a random number of players of at least 2
    while (numPlayers < 2)
    {
      numPlayers = floor(Random() * (MAX_PLAYERS+1));
    }

    //initialize testGame numPlayers to random amount of players
    testGame.numPlayers = numPlayers;

    //loop to initialize random decks, discards, and hands
    for (j = 0; j < numPlayers; j++)
    {
      testGame.deckCount[j] = floor(Random() * MAX_DECK);
      testGame.discardCount[j] = floor(Random() * MAX_DECK);
      testGame.handCount[j] = floor(Random() * MAX_HAND);

      //initializing random hands for each player
      for (i = 0; i < testGame.handCount[j]; i++)
      {
        testGame.hand[j][i] = floor(Random() * MAX_DECK);
      }

      //initializing random discards for each player
      for (i = 0; i < testGame.discardCount[j]; i++)
      {
        testGame.discard[j][i] = floor(Random() * MAX_DECK);
      }

      //initializing random deck for each player
      for (i = 0; i < testGame.discardCount[j]; i++)
      {
        testGame.deck[j][i] = floor(Random() * MAX_DECK);
      }
    }
    //function call to test the getWinners()
    testGetWinners(players, &testGame);
  }

  printf ("ALL TESTS OK!\n\n");

  exit(0);
}