/* -----------------------------------------------------------------------
 *  Test simthyRefactor()
 *  Include the following lines in your makefile:
 *
 *  cardtest1: cardtest1.c dominion.o rngs.o
 *	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./cardtest1" to run
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
    int player, before_hand, before_playCard, before_deck, after_hand, after_playCard, after_deck;
    int handPos;
    int k[12] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward};
    printf("+++++smithyRefactor() tests begin+++++\n");
    initializeGame(numPlayer, k, 2, &G); // init a game
    
    // test playing simity card for each player
    for (player = 0; player < numPlayer; player++){
        G.hand[player][G.handCount[player]] = smithy; // player gets the smithy card
        G.handCount[player]++;
        before_hand = G.handCount[player]; // record the total cards number in hand
        before_deck = G.deckCount[player]; // record the total cards number in deck
        before_playCard = G.playedCardCount; // record the play cards number
        
        handPos = G.handCount[player] - 1; // record the smithy card position
        smithyRefactor (&player, &G, &handPos); // play the smithy card
        
        after_hand = G.handCount[player]; // record the total cards number in hand
        after_deck = G.deckCount[player]; // record the total cards number in deck
        after_playCard = G.playedCardCount; // record the play cards number

        printf("-------------Test player %d----------------.\n", player);
        printf("Test player %d had %d card(s) in hand before, and %d card(s) after playing smithy.\n", player, before_hand, after_hand);
        printf("Test player %d had %d card(s) in deck before, and %d card(s) after playing smithy.\n", player, before_deck, after_deck);
        printf("Test player %d had %d playcard(s) before, and %d playcard(s) after playing smithy.\n", player, before_playCard, after_playCard);
        
        assert(after_hand == before_hand + 2); // get 3 new cards and played smithy card, so user has 3 - 1 = 2 more cards in hand now.
        assert(before_deck - 3 == after_deck); // deck lost 3 card now.
        assert(before_playCard + 1 == after_playCard); // smithy card goes to playcards.
        
    }
    printf("+++++smithyRefactor() test passed+++++\n");
    
}

int main(int argc, char *argv[]){
    testSmithyRefactor();
    return 0;
}

