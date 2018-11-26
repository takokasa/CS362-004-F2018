/* -----------------------------------------------------------------------
 * Test for greatHallRefactor()
 * Include the following lines in your makefile:
 *
 *  cardtest4: cardtest4.c dominion.o rngs.o
 *	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 *
 * type "./cardtest4" to run
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

void testGreatHallRefactor(){
    int numPlayer = 2;
    struct gameState G;
    int player, before_hand, before_playCard, before_deck, before_action, after_hand, after_playCard, after_deck, after_action;
    
    int handPos;
    int k[12] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward};
    printf("++++++greatHallRefactor() tests begin+++++\n");
    
    initializeGame(numPlayer, k, 2, &G); // init a game
        // test playing greatHall card for each player
    for (player = 0; player < numPlayer; player++){
        G.hand[player][G.handCount[player]] = great_hall; // player gets the great_hall card
        G.handCount[player]++;
        handPos = G.handCount[player] - 1; // record the great_hall card position
        
        before_hand = G.handCount[player]; // record the total cards number in hand
        before_deck = G.deckCount[player]; // record the total cards number in deck
        before_playCard = G.playedCardCount; // record the play cards number
        before_action = G.numActions;

        greatHallRefactor(&player, &G, &handPos);//play the great_hall card
        
        after_hand = G.handCount[player]; // record the total cards number in hand
        after_deck = G.deckCount[player]; // record the total cards number in deck
        after_playCard = G.playedCardCount; // record the play cards number
        after_action = G.numActions;
        
        printf("-------------Test player %d----------------.\n", player);
        printf("Test player %d had %d card(s) in hand before, and %d card(s) after playing great_hall.\n", player, before_hand, after_hand);
        printf("Test player %d had %d card(s) in deck before, and %d card(s) after playing great_hall.\n", player, before_deck, after_deck);
        printf("Test player %d had %d playcard(s) before, and %d playcard(s) after playing great_hall.\n", player, before_playCard, after_playCard);
        printf("Test player %d had %d actions, but now has %d actions after playing great_hall.\n", player, before_action, after_action);
        
        assert(before_hand == after_hand); // get 1 new card in hand now but used great_hall.
        assert(before_deck - 1 == after_deck); // deck lost 1 card now.
        assert(before_playCard + 1 == after_playCard); // great_hall card goes to playcards.
        assert(before_action + 1 == after_action); // gets 1 more actions
    }
    printf("+++++greatHallRefactor() test passed+++++\n");
    
}

int main(int argc, char *argv[]){
    testGreatHallRefactor();
    return 0;
}



