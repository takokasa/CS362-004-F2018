/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testIsGameOver: testIsGameOver.c dominion.o rngs.o
 *  gcc -o testIsGameOver -g  testIsGameOver.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./testIsGameOver" to run
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

// int isGameOver(struct gameState *state) {
//   int i;
//   int j;
	
//   //if stack of Province cards is empty, the game ends
//   if (state->supplyCount[province] == 0)
//     {
//       return 1;
//     }

//   //if three supply pile are at 0, the game ends
//   j = 0;
//   for (i = 0; i < 25; i++)
//     {
//       if (state->supplyCount[i] == 0)
// 	{
// 	  j++;
// 	}
//     }
//   if ( j >= 3)
//     {
//       return 1;
//     }

//   return 0;
// }

void testIsGameOver () {
  struct gameState G;
  int i;
  printf ("TESTING isGameOver():\n");

  for (i = 0; i < 25; i++){
    G.supplyCount[i] = 10;
  }

  // test 1
  assert(isGameOver(&G) == 0); // not game over
  // test 2
  G.supplyCount[province] = 0; // set province count = 0
  assert(isGameOver(&G) == 1); // game over
  // test 3
  G.supplyCount[province] = 1; // now you have non empty province cards, game should continue normally
  G.supplyCount[curse] = 0;
  G.supplyCount[estate] = 0;
  G.supplyCount[gold] = 0;
  assert(isGameOver(&G) == 1); // game should end because three piles are empty
  // test 4
   G.supplyCount[curse] = 1; // curse is no longer empty
   G.supplyCount[estate] = 0;
   G.supplyCount[gold] = 0;
   assert(isGameOver(&G) == 0); // Game should not end because three supply piles are not empty
   
   printf ("All tests for isGameOver() passed!\n");
}

int main(int argc, char *argv[]){
    testIsGameOver();
    return 0;
}
