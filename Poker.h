/*****************************************************************
* Author: Blake Turman
*		  Started from code by Deitel & Deitel - C How to Program
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: PA 7
* Last Updated: November 20, 2024
* Description: This program plays a virtual game of Poker (5-card
*			   draw) between a player and a dealer.
*****************************************************************/
#ifndef POKER_H
#define POKER_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct card
{
	int face_index,
		suit_index;
}Card;

typedef struct hand
{
	Card arr[5];
}Hand;

/**********************************************************
* Function: shuffle()
* Description: Fills deck with random row and coloumn 
*			   indeces.
* Input Parameters: none
* Output Parameters: int wDeck[][13]
* Returns: nothing
* Preconditions: all deck slots must be null
*				 wDeck has 4 colomns and 13 rows
*				 random seed must be set
*				 includes <stdlib>
* Credit: by Deitel & Deitel - C How to Program
* ********************************************************/
void shuffle(int wDeck[][13]);

/**********************************************************
* Function: initialize_deck()
* Description: Reinitializes deck array since shuffle()
*			   only works once.
* Input Parameters: none
* Output Parameters: int wDeck[][13]
* Returns: nothing
* Preconditions: wDeck has 4 colomns and 13 rows
* Credit: modified from Deitel & Deitel - C How to Program
* ********************************************************/
void initialize_deck(int wDeck[][13]);

/**********************************************************
* Function: deal()
* Description: Fills player hand array with num cards
*			   starting from given index of wDeck. Returns 
*			   index of next card to be drawn.
* Input Parameters: const int wDeck[][13], int num, 
*				    int index
* Output Parameters: Hand* player_hand
* Returns: int
* Preconditions: wDeck has 4 colomns and 13 rows
*				 num should not excede player hand
* Credit: modified from Deitel & Deitel - C How to Program
* ********************************************************/
int deal(Hand* player_hand, const int wDeck[][13], int num, int index);

/**********************************************************
* Function: draw_one()
* Description: Places the card specified at deck_index 
*			   into the player_hand array at the specified
*			   hand_index. Returns index of next card to 
*			   be drawn.
* Input Parameters: const int wDeck[][13], int hand_index,
*				    int deck_index
* Output Parameters: Hand* player_hand
* Returns: int
* Preconditions: wDeck has 4 colomns and 13 rows
* ********************************************************/
int draw_one(Hand* player_hand, const int wDeck[][13], int hand_index, int deck_index);

/**********************************************************
* Function: print_hand()
* Description: Prints all cards in user hand, with
*			   formatting. Input 1 for style for numbered
*			   list or else for default.
* Input Parameters: Hand player_hand, 
*					const int wDeck[][13], 
*					const char* wFace[], 
*					const char* wSuit[], 
*					int size, int style
* Output Parameters: none
* Returns: nothing
* Preconditions: wDeck has 4 colomns and 13 rows
*				 includes <stdio.h>
* Credit: modified from Deitel & Deitel - C How to Program
* ********************************************************/
void print_hand(Hand player_hand, const int wDeck[][13], const char* wFace[], const char* wSuit[], int size, int style);

/**********************************************************
* Function: discard()
* Description: Prompts player which cards they want to 
*			   discard repeating until valid input. 
*			   Indeces of player input are output as
*			   discard1, 2 and 3. If player does not give
*			   all three inputs, then -1 will be output in
*			   the unused discard parameters.
* Input Parameters: int size
* Output Parameters: int* discard1, int* discard2, 
*					 int* discard3
* Returns: nothing
* Preconditions: includes <stdio.h>
* ********************************************************/
void discard(int size, int* discard1, int* discard2, int* discard3);

/**********************************************************
* Function: dealer_ai()
* Description: Makes strategic selection of discards based
*			   on input player hand. Indeces of discards 
*			   are output as discard1, 2 and 3. If not all 
*			   discards are used, then -1 will be output 
*			   in the unused discard parameters.
* Input Parameters: Hand player_hand, int size
* Output Parameters: int* discard1, int* discard2, 
*					 int* discard3
* Returns: nothing
* Preconditions: includes local header "Poker.h"
*				 includes <limits.h>
* ********************************************************/
void dealer_ai(Hand player_hand, int size, int* discard1, int* discard2, int* discard3);

/**********************************************************
* Function: is_pair()
* Description: Checks if pair exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_pair(Hand player_hand, int size);

/**********************************************************
* Function: is_two_pair()
* Description: Checks if two pair exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_two_pair(Hand player_hand, int size);

/**********************************************************
* Function: is_three_of_a_kind()
* Description: Checks if three of a kind exists in 
*			   player_hand. Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_three_of_a_kind(Hand player_hand, int size);

/**********************************************************
* Function: is_four_of_a_kind()
* Description: Checks if four of a kind exists in
*			   player_hand. Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_four_of_a_kind(Hand player_hand, int size);

/**********************************************************
* Function: is_four_of_a_kind()
* Description: Checks if full house exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: includes local header "Poker.h"
* ********************************************************/
int is_full_house(Hand player_hand, int size);

/**********************************************************
* Function: is_four_of_a_kind()
* Description: Checks if flush exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_flush(Hand player_hand, int size);

/**********************************************************
* Function: is_straight()
* Description: Checks if 5 straight exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int is_straight(Hand player_hand, int size);

/**********************************************************
* Function: is_royal_flush()
* Description: Checks if royal flush exists in player_hand.
*			   Returns 1 if so and 0 if not.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: int
* Preconditions: includes local header "Poker.h"
* ********************************************************/
int is_royal_flush(Hand player_hand, int size);

/**********************************************************
* Function: who_wins()
* Description: Determines which of the two poker hands 
*			   won. Returns 1 if player1_hand was better,
*			   2 if player2_hand was better, or 0 if tie.
* Input Parameters: Hand player1_hand, Hand player2_hand, 
*					int size
* Output Parameters: none
* Returns: int
* Preconditions: includes local header "Poker.h"
*			     includes <stdio.h>
* ********************************************************/
int who_wins(Hand player1_hand, Hand player2_hand, int size);

/**********************************************************
* Function: who_wins()
* Description: Prints the highest ranking card combination
*			   that exists in player_hand.
* Input Parameters: Hand player_hand, int size
* Output Parameters: none
* Returns: nothing
* Preconditions: includes local header "Poker.h"
*			     includes <stdio.h>
* ********************************************************/
void print_current_best_hand(Hand player_hand, int size);

/**********************************************************
* Function: menu()
* Description: Displays menu and gets selection input from
*			   player. Returns player's selection input.
* Input Parameters: none
* Output Parameters: none
* Returns: int
* Preconditions: includes <stdio.h>
* ********************************************************/
int menu(void);

/**********************************************************
* Function: menu()
* Description: Prompts bet amount from player, repeating
*			   until valid input. Returns int amount * 100
*			   from player input. 1 for style input
*			   prompts initial bet, and else prompts raise
*			   amount.
* Input Parameters: int style
* Output Parameters: none
* Returns: int
* Preconditions: includes <stdio.h>
*				 includes <ctype.h>
*				 includes <string.h>
*				 includes <math.h>
* ********************************************************/
int get_bet(int style);

#endif // !POKER_H