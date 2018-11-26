/* -----------------------------------------------------------------------
 * Test for villageRefactor()
 * Include the following lines in your makefile:
 *
 *  cardtest3: cardtest3.c dominion.o rngs.o
 *	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./cardtest3" to run
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

void testVillageRefactor(){
    int numPlayer = 2;
    struct gameState G;
    int player, before_hand, before_playCard, before_deck, before_action, after_hand, after_playCard, after_deck, after_action;
    
    int handPos;
    int k[12] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward};
    
    printf("+++++villageRefactor() tests begin+++++\n");
    
    initializeGame(numPlayer, k, 2, &G); // init a game
        // test playing village card for each player
    for (player = 0; player < numPlayer; player++){
        G.hand[player][G.handCount[player]] = village; // player gets the village card
        G.handCount[player]++;
        handPos = G.handCount[player] - 1; // record the village card position
        
        before_hand = G.handCount[player]; // record the total cards number in hand
        before_deck = G.deckCount[player]; // record the total cards number in deck
        before_playCard = G.playedCardCount; // record the play cards number
        before_action = G.numActions;

        // villageRefactor(&player, &G, &handPos);//play the adventure card
        cardVillage(player, &G, handPos);
        after_hand = G.handCount[player]; // record the total cards number in hand
        after_deck = G.deckCount[player]; // record the total cards number in deck
        after_playCard = G.playedCardCount; // record the play cards number
        after_action = G.numActions;
        
        printf("-------------Test player %d----------------.\n", player);
        printf("Test player %d had %d card(s) in hand before, and %d card(s) after playing village.\n", player, before_hand, after_hand);
        printf("Test player %d had %d card(s) in deck before, and %d card(s) after playing village.\n", player, before_deck, after_deck);
        printf("Test player %d had %d playcard(s) before, and %d playcard(s) after playing village.\n", player, before_playCard, after_playCard);
        printf("Test player %d had %d actions, but now has %d actions after playing village.\n", player, before_action, after_action);
        
        assert(before_hand == after_hand); // get 1 new card in hand now but used village.
        assert(before_deck - 1 == after_deck); // deck lost 1 card now.
        assert(before_playCard + 1 == after_playCard); // village card goes to playcards.
        assert(before_action + 2 == after_action); // gets 2 more actions
    }
    printf("+++++villageRefactor() test passed+++++\n");
    
}

int main(int argc, char *argv[]){
    testVillageRefactor();
    return 0;
}


