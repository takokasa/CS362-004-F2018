/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 *  cardtest1: cardtest1.c dominion.o rngs.o
 *	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./tcardtest1" to run
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

void testSmithyRefactor(){
    int numPlayer = 2;
    struct gameState G;
    int i, before, after, handPos;
    
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
    printf("SmithyRefactor() tests begin\n");
    initializeGame(numPlayer, k, 2, &G); // init a game
    
    // test playing smithy card for each player
    for (i = 0; i < numPlayer; i++){
        G.hand[i][G.handCount[i]] = smithy; // player gets the smithy card
        G.handCount[i]++;
        before = G.handCount[i]; // record the current cards number in hand
        handPos = G.hand[i][G.handCount[i]] - 1;
        smithyRefactor (&i, &G, &handPos); // play the smithy card
        after = G.handCount[i]; // record the current cards number in hand
        printf("Test player %d had %d card(s), but now has %d cards after playing smithy.\n", i, before, after);
        assert(after == before + 2); // get 3 new cards and played smithy card, so user has 3 - 1 = 2 more cards in hand now.
    }
    printf("smithyRefactor() test passed\n");
    
}

int main(int argc, char *argv[]){
    testSmithyRefactor();
    return 0;
}

