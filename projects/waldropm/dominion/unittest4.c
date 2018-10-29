/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 *  testSupplyCount: testSupplyCount dominion.o rngs.o
 *	gcc -o testSupplyCount -g  testSupplyCount.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./testSupplyCount" to run
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

void setSupplyCount(int numPlayers, struct gameState *state){
        //initialize supply
    ///////////////////////////////
    
    //set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }
    
    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }
    
    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;
}


void testSupplyCount(){
    struct gameState G;
    printf ("TESTING supplyCount():\n");
    
    // test for 2 players
    setSupplyCount(2, &G);
    assert(supplyCount(curse, &G) == 10);
    assert(supplyCount(estate, &G) == 8);
    assert(supplyCount(duchy, &G) == 8);
    assert(supplyCount(province, &G) == 8);
    
    assert(supplyCount(copper, &G) == 60 - 7*2);
    assert(supplyCount(silver, &G) == 40);
    assert(supplyCount(gold, &G) == 30);
    
    // test for 3 players
    memset(&G, 0, sizeof(G));// clear the game state
    setSupplyCount(3, &G);
    assert(supplyCount(curse, &G) == 20);
    assert(supplyCount(estate, &G) == 12);
    assert(supplyCount(duchy, &G) == 12);
    assert(supplyCount(province, &G) == 12);
    
    assert(supplyCount(copper, &G) == 60 - 7*3);
    assert(supplyCount(silver, &G) == 40);
    assert(supplyCount(gold, &G) == 30);

    // test for 6 players
    memset(&G, 0, sizeof(G));// clear the game state
    setSupplyCount(6, &G);
    assert(supplyCount(curse, &G) == 30);
    assert(supplyCount(estate, &G) == 12);
    assert(supplyCount(duchy, &G) == 12);
    assert(supplyCount(province, &G) == 12);
    
    assert(supplyCount(copper, &G) == 60 - 7*6);
    assert(supplyCount(silver, &G) == 40);
    assert(supplyCount(gold, &G) == 30);
    
    printf("All tests passed!\n");
    
}

int main(int argc, char *argv[]){
    testSupplyCount();
    return 0;
}
