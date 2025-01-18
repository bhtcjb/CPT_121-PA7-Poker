/*****************************************************************
* Author: Blake Turman
*		  Started from code by Deitel & Deitel - C How to Program
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: PA 7
* Last Updated: November 20, 2024
* Description: This program plays a virtual game of Poker (5-card
*			   draw) between a player and a dealer.
*****************************************************************/
#include "Poker.h"


int main(void)
{
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	int cards_drawn = 1,
		p1_temp_discard1 = 0,
		p1_temp_discard2 = 0,
		p1_temp_discard3 = 0,
		p2_temp_discard1 = 0,
		p2_temp_discard2 = 0,
		p2_temp_discard3 = 0,
		winner = -1,
		menu_input = 0,
		num_wins = 0,
		num_losses = 0,
		money_earned = 0,
		bet = 0;

	char exit = '\0';

	Hand p1_hand,
		p2_hand;

	srand((unsigned)time(NULL)); /* seed random-number generator */

	do
	{
		// display menu
		system("cls");
		menu_input = menu();

		//display rules
		if (menu_input == 1)
		{
			system("cls");
			printf("Rules of 5-Card Draw:\n1. The dealer will deal five cards to you and themselves.\n"
				"2. You will look at your hand and decide a bet. "
				"3. After betting, you will be able discard up to 3 cards from your hand or leave it as so,"
				" and the dealer is able to do the same.\n"
				"4. All discarded cards will be replaced by the dealer such that both you and the "
				"dealer have 5 cards again.\n"
				"5. You will look hand your new modified hand, and a second round of betting will take place\n"
				"6. At this point all cards will be shown and a winner will be determined.\n\n"
				"Precendences:\n 1. Royal Flush\n 2. Straight Flush\n 3. Four of a Kind\n 4. Full House\n"
				" 5. Flush\n 6. Straight\n 7. Three of a Kind\n 8. Two Pair\n 9. Pair\n10. High Card\n\n");
			system("pause");
		}

		// play game
		else if (menu_input == 2)
		{
			num_wins = 0;
			num_losses = 0;
			money_earned = 0;
			do
			{
				cards_drawn = 1;

				system("cls");
				printf("Dealing Cards. . .\n\n");
				system("pause>nul");
				system("cls");

				// shuffle deck
				initialize_deck(deck);
				shuffle(deck);

				// deal initial hands
				for (int i = 0; i < 5; ++i) // alternates deal 1 card to each player
				{
					cards_drawn = draw_one(&p1_hand, deck, i, cards_drawn);
					cards_drawn = draw_one(&p2_hand, deck, i, cards_drawn);
				}


				// show hand
				printf("Your Hand\n\n");
				print_hand(p1_hand, deck, face, suit, 5, 0);

				print_current_best_hand(p1_hand, 5);

				putchar('\n');
				
				bet = get_bet(1);

				system("cls");

				// prompt discard
				printf("Select cards you would like to discard (max 3):\n\n");
				print_hand(p1_hand, deck, face, suit, 5, 1);
				discard(5, &p1_temp_discard1, &p1_temp_discard2, &p1_temp_discard3);
				dealer_ai(p2_hand, 5, &p2_temp_discard1, &p2_temp_discard2, &p2_temp_discard3);

				// redraw discarded cards
				if (p1_temp_discard1 != -1) // alternates between player and dealer
				{
					cards_drawn = draw_one(&p1_hand, deck, p1_temp_discard1, cards_drawn);
				}
				if (p2_temp_discard1 != -1)
				{
					cards_drawn = draw_one(&p2_hand, deck, p2_temp_discard1, cards_drawn);
				}
				if (p1_temp_discard2 != -1)
				{
					cards_drawn = draw_one(&p1_hand, deck, p1_temp_discard2, cards_drawn);
				}
				if (p2_temp_discard2 != -1)
				{
					cards_drawn = draw_one(&p2_hand, deck, p2_temp_discard2, cards_drawn);
				}
				if (p1_temp_discard3 != -1)
				{
					cards_drawn = draw_one(&p1_hand, deck, p1_temp_discard3, cards_drawn);
				}
				if (p2_temp_discard3 != -1)
				{
					cards_drawn = draw_one(&p2_hand, deck, p2_temp_discard3, cards_drawn);
				}

				// reshow hand
				system("cls");
				printf("Your Hand\n\n");
				print_hand(p1_hand, deck, face, suit, 5, 0);

				print_current_best_hand(p1_hand, 5);

				putchar('\n');

				bet += get_bet(0);
				
				system("cls");



				// display winner
				printf("Your Hand\n\n");
				print_hand(p1_hand, deck, face, suit, 5, 0);
				putchar('\n');
				putchar('\n');

				printf("Dealer's Hand\n\n");
				print_hand(p2_hand, deck, face, suit, 5, 0);

				putchar('\n');
				putchar('\n');

				winner = who_wins(p1_hand, p2_hand, 5);

				putchar('\n');
				putchar('\n');
				system("pause");
				system("cls");

				if (winner == 1)
				{
					printf("You Win!\n");
					printf("\n+$%.2lf\n", (double)bet / 100);
					money_earned += bet;
					++num_wins;
				}
				else if (winner == 2)
				{
					printf("You Lose!\n");
					printf("\n-$%.2lf\n", (double)bet / 100);
					money_earned -= bet;
					++num_losses;
				}
				else if (winner == 0)
				{
					printf("It's a Tie!\n");
					printf("\n+--.--\n");
				}

				putchar('\n');
				system("pause");
				system("cls");

				// prompt stay or leave
				printf("Win Percentage: %%%.2lf\n", (double)num_wins / (num_losses + num_wins) * 100);
				printf("Money Earned: $%.2lf\n\n", (double)money_earned / 100);
				printf("Would you like to quit to menu? y or n? ");
				scanf(" %c", &exit);
				rewind(stdin);



			} while (exit != 'y');
		}
	}while (menu_input != 3);

	system("cls");
	printf("Now Exiting. . .\n\n");

	return 0;
}

