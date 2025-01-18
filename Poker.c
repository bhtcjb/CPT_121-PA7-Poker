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

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

void initialize_deck(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */


		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				wDeck[row][column] = 0;
			}
		}
}

/* deal cards in deck */
int deal(Hand* player_hand, const int wDeck[][13], int num, int index)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* deal each of the num cards */
	for (card = index; card <= num + index - 1; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					player_hand->arr[card - index].face_index = column;
					player_hand->arr[card - index].suit_index = row;
				}
			}
		}
	}
	return num + index;
}

int draw_one(Hand* player_hand, const int wDeck[][13], int hand_index, int deck_index)
{
	for (int row = 0; row <= 3; row++)
	{
		for (int column = 0; column <= 12; column++)
		{
			if (wDeck[row][column] == deck_index)
			{
				player_hand->arr[hand_index].face_index = column;
				player_hand->arr[hand_index].suit_index = row;
			}
		}
	}

	return ++deck_index;
}

void print_hand(Hand player_hand, const int wDeck[][13], const char* wFace[], const char* wSuit[], int size, int style)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* deal each of the 52 cards */
	for (card = 1; card <= size; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					if (style != 1)
					{
						printf("%5s of %-8s%c", wFace[player_hand.arr[card - 1].face_index],
							wSuit[player_hand.arr[card - 1].suit_index], card % 2 == 0 ? '\n' : '\t');
					}
					else
					{
						printf("%d.%5s of %-8s\n", card, wFace[player_hand.arr[card - 1].face_index],
							wSuit[player_hand.arr[card - 1].suit_index]);
					}
				}
			}
		}
	}
}

void discard(int size, int* discard1, int* discard2, int* discard3)
{

	char arr[20] = { '\0' };
	int check = 0,
		num_char = 0;

	do
	{
		check = 1;

		printf("\nPlease enter up to 3 integers: ");
		fgets(&arr, 20, stdin);
		
		num_char = 0;
		for (int i = 0; arr[i] != '\0'; ++i)
		{
			if ((arr[i] != ' ' && arr[i] != '\n'))
			{
				arr[num_char++] = arr[i];
			}
		}

		if (num_char == 0)
		{
			*discard1 = -1;
			*discard2 = -1;
			*discard3 = -1;
		}
		else if (num_char == 1)
		{
			*discard1 = (int)arr[0] - '1';
			if (*discard1 < 0 || *discard1 >= size)
			{
				printf("\nInvalid Input\n");
				check = 0;
			}
			*discard2 = -1;
			*discard3 = -1;
		}
		else if (num_char == 2)
		{
			*discard1 = (int)arr[0] - '1';
			*discard2 = (int)arr[1] - '1';
			if (*discard1 < 0 || *discard1 >= size || *discard2 < 0 || *discard2 >= size ||
				*discard1 == *discard2)
			{
				printf("\nInvalid Input\n");
				check = 0;
			}
			*discard3 = -1;
		}
		else if (num_char == 3)
		{
			*discard1 = (int)arr[0] - '1';
			*discard2 = (int)arr[1] - '1';
			*discard3 = (int)arr[2] - '1';
			if (*discard1 < 0 || *discard1 >= size || *discard2 < 0 || *discard2 >= size ||
				*discard3 < 0 || *discard3 >= size || *discard1 == *discard2 || *discard2 == *discard3 ||
				*discard1 == *discard3)
			{
				printf("\nInvalid Input\n");
				check = 0;
			}
		}
		else if (num_char > 3)
		{
			printf("\nInvalid Input\n");
			check = 0;
		}	
		
	} while (check != 1);


	rewind(stdin);
}

void dealer_ai(Hand player_hand, int size, int* discard1, int* discard2, int* discard3)
{
	int straight_check = 0,
		most_faces = -1,
		most_suits = -1,
		least_faces = INT_MAX,
		least_suits = INT_MAX,
		least_faces_index1 = -1,
		least_faces_index2 = -1,
		least_faces_index3 = -1,
		least_suits_index = -1,
		num_faces[13] = { 0 },
		num_suits[4] = { 0 };

	*discard1 = -1;
	*discard2 = -1;
	*discard3 = -1;

	//fill array
	for (int i = 0; i < size; ++i)
	{
		++num_faces[player_hand.arr[i].face_index];
		++num_suits[player_hand.arr[i].suit_index];
	}

	// looks at faces
	for (int i = 0; i < 13; ++i)
	{
		if (num_faces[i] > most_faces)
		{
			most_faces = num_faces[i];
		}
		if (num_faces[i] != 0 && num_faces[i] < least_faces)
		{
			least_faces = num_faces[i];
			least_faces_index1 = i;
		}
	}
	least_faces = INT_MAX;
	for (int i = 0; i < 13; ++i)
	{
		if (num_faces[i] != 0 && num_faces[i] < least_faces && i != least_faces_index1)
		{
			least_faces = num_faces[i];
			least_faces_index2 = i;
		}
	}
	least_faces = INT_MAX;
	for (int i = 0; i < 13; ++i)
	{
		if (num_faces[i] != 0 && num_faces[i] < least_faces && i != least_faces_index1
			&& i != least_faces_index2)
		{
			least_faces = num_faces[i];
			least_faces_index3 = i;
		}
	}

	//looks at suits
	for (int i = 0; i < 4; ++i)
	{
		if (num_suits[i] > most_suits)
		{
			most_suits = num_suits[i];
		}
		if (num_suits[i] != 0 && num_suits[i] < least_suits)
		{
			least_suits = num_suits[i];
			least_suits_index = i;
		}
	}

	if ((is_royal_flush(player_hand, size) || is_flush(player_hand, size) || is_full_house(player_hand, size) ||
		is_straight(player_hand, size)))
	{
	}
	else if (is_four_of_a_kind(player_hand, size))
	{
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].face_index == least_faces_index1)
			{
				*discard1 = i;
				i = size;
			}
		}
	}
	else if (most_suits >= 4)
	{
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].suit_index == least_suits_index)
			{
				*discard1 = i;
				i = size;
			}
		}
	}
	else if (most_faces == 3)
	{
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].face_index == least_faces_index1)
			{
				*discard1 = i;
				i = size;
			}
		}
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].face_index == least_faces_index2)
			{
				*discard2 = i;
				i = size;
			}
		}
	}
	else if (is_two_pair(player_hand, size))
	{
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].face_index == least_faces_index1)
			{
				*discard1 = i;
				i = size;
			}
		}
	}
	else
	{
		for (int i = 0; i < 13; ++i)
		{
			if (num_faces[i] > 0)
			{
				++straight_check;
			}
			else
			{
				if (straight_check > 3)
				{
					i = 13;
				}
				else
				{
					straight_check = 0;
				}
			}
		}
		if (straight_check > 3)
		{
			for (int i = 0; i < 13; ++i)
			{
				if (num_faces[i] > 0 && i - 1 < 0 && num_faces[i + 1] == 0)
				{
					for (int j = 0; j < size; ++j)
					{
						if (player_hand.arr[j].face_index == i)
						{
							*discard1 = j;
							j = size;
							i = 13;
						}
					}
				}
				else if (num_faces[i] > 0 && i + 1 > 12 && num_faces[i - 1] == 0)
				{
					for (int j = 0; j < size; ++j)
					{
						if (player_hand.arr[j].face_index == i)
						{
							*discard1 = j;
							j = size;
							i = 13;
						}
					}
				}
				else if (num_faces[i] > 0 && num_faces[i - 1] == 0 && num_faces[i + 1] == 0)
				{
					for (int j = 0; j < size; ++j)
					{
						if (player_hand.arr[j].face_index == i)
						{
							*discard1 = j;
							j = size;
							i = 13;
						}
					}
				}
				else if (num_faces[i] > 1)
				{
					for (int j = 0; j < size; ++j)
					{
						if (player_hand.arr[j].face_index == i)
						{
							*discard1 = j;
							j = size;
							i = 13;
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < size; ++i)
			{
				if (player_hand.arr[i].face_index == least_faces_index1)
				{
					*discard1 = i;
					i = size;
				}

			}
			for (int i = 0; i < size; ++i)
			{
				if (player_hand.arr[i].face_index == least_faces_index2)
				{
					*discard2 = i;
					i = size;
				}
			}
			for (int i = 0; i < size; ++i)
			{
				if (player_hand.arr[i].face_index == least_faces_index3)
				{
					*discard3 = i;
					i = size;
				}
			}

		}

	}
}

int is_pair(Hand player_hand, int size)
{
	int check = 0;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (player_hand.arr[i].face_index == player_hand.arr[j].face_index)
			{
				check = 1;
			}
		}
	}

	return check;
}

int is_two_pair(Hand player_hand, int size)
{
	int check = 0,
		temp = -1;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (player_hand.arr[i].face_index == player_hand.arr[j].face_index && player_hand.arr[i].face_index != temp)
			{
				temp = player_hand.arr[i].face_index;
				++check;
			}
		}
	}

	return (check > 1);
}

int is_three_of_a_kind(Hand player_hand, int size)
{
	int check = 0,
		temp = -1;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (player_hand.arr[i].face_index == player_hand.arr[j].face_index)
			{
				temp = player_hand.arr[i].face_index;		

				for (int k = 0; k < size; ++k)
				{
					if (player_hand.arr[k].face_index == temp)
					{
						++check;
					}
				}
				check *= (check > 2);
			}
			
		}
	}

	return (check > 2);
}

int is_four_of_a_kind(Hand player_hand, int size)
{
	int check = 0,
		temp = -1;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (player_hand.arr[i].face_index == player_hand.arr[j].face_index)
			{
				temp = player_hand.arr[i].face_index;

				for (int k = 0; k < size; ++k)
				{
					if (player_hand.arr[k].face_index == temp)
					{
						++check;
					}
				}
				check *= (check > 3);
			}

		}
	}

	return (check > 3);
}

int is_full_house(Hand player_hand, int size)
{
	int check = 0;

	if (is_three_of_a_kind(player_hand, size) && is_two_pair(player_hand, size))
	{
		check = 1;
	}

	return check;
}

int is_flush(Hand player_hand, int size)
{
	int check = 0,
		temp = -1;

	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (player_hand.arr[i].suit_index == player_hand.arr[j].suit_index)
			{
				temp = player_hand.arr[i].suit_index;

				for (int k = 0; k < size; ++k)
				{
					if (player_hand.arr[k].suit_index == temp)
					{
						++check;
					}
				}
				check *= (check > 4);
			}

		}
	}

	return (check > 4);
}

int is_straight(Hand player_hand, int size)
{
	int check = 0,
		num_faces[13] = { 0 };

	//fill array with player values in order
	for (int i = 0; i < size; ++i)
	{
			++num_faces[player_hand.arr[i].face_index];	
	}

	//check if 5 in a row
	for (int i = 0; i < 13; ++i)
	{
			if (num_faces[i] > 0)
			{
				++check;
			}
			else
			{
				if (check > 4)
				{
					i = 13;
				}
				else
				{
					check = 0;
				}
			}
	}

	return (check > 4);
}

int is_royal_flush(Hand player_hand, int size)
{
	int royal_arr[5] = { 0 },
		check = 1;

	if (is_flush(player_hand, size))
	{
		for (int i = 0; i < size; ++i)
		{
			if (player_hand.arr[i].face_index == 0)
			{
				royal_arr[0] += 1;
			}
			else if (player_hand.arr[i].face_index == 9)
			{
				royal_arr[1] += 1;
			}
			else if (player_hand.arr[i].face_index == 10)
			{
				royal_arr[2] += 1;
			}
			else if (player_hand.arr[i].face_index == 11)
			{
				royal_arr[3] += 1;
			}
			else if (player_hand.arr[i].face_index == 12)
			{
				royal_arr[4] += 1;
			}
		}

		for (int i = 0; i < 5; ++i)
		{
			if (royal_arr[i] == NULL)
			{
				check = 0;
				i = 5;
			}
		}
	}
	else
	{
		check = 0;
	}
	return check;
}

int who_wins(Hand player1_hand, Hand player2_hand, int size) 
{
	int winner = 0,
		p1_precedence = 0,
		p2_precedence = 0,
		num_faces_p1[13] = { 0 },
		num_faces_p2[13] = { 0 };

	printf("You Have:\n");

	if (is_flush(player1_hand, size))
	{
		if (is_royal_flush(player1_hand, size))
		{
			printf("Royal Flush!\n\n");
			p1_precedence = 1;
		}
		else if (is_straight(player1_hand, size))
		{
			printf("Straight Flush!\n\n");
			p1_precedence = 2;
		}
		else
		{
			printf("Flush!\n\n");
			p1_precedence = 5;
		}
	}
	else if (is_four_of_a_kind(player1_hand, size))
	{
		printf("Four of a Kind!\n\n");
		p1_precedence = 3;
	}
	else if (is_full_house(player1_hand, size))
	{
		printf("Full House!\n\n");
		p1_precedence = 4;
	}
	else if (is_straight(player1_hand, size))
	{
		printf("Straight!\n\n");
		p1_precedence = 6;
	}
	else if (is_three_of_a_kind(player1_hand, size))
	{
		printf("Three of a Kind!\n\n");
		p1_precedence = 7;
	}
	else if (is_two_pair(player1_hand, size))
	{
		printf("Two Pair!\n\n");
		p1_precedence = 8;
	}
	else if (is_pair(player1_hand, size))
	{
		printf("Pair!\n\n");
		p1_precedence = 9;
	}
	else
	{
		printf("High Card!\n\n");
		p1_precedence = 10;
	}

	printf("Dealer Has:\n");

	if (is_flush(player2_hand, size))
	{
		if (is_royal_flush(player2_hand, size))
		{
			printf("Royal Flush!\n\n");
			p2_precedence = 1;
		}
		else if (is_straight(player2_hand, size))
		{
			printf("Straight Flush!\n\n");
			p2_precedence = 2;
		}
		else
		{
			printf("Flush!\n\n");
			p2_precedence = 5;
		}
	}
	else if (is_four_of_a_kind(player2_hand, size))
	{
		printf("Four of a Kind!\n\n");
		p2_precedence = 3;
	}
	else if (is_full_house(player2_hand, size))
	{
		printf("Full House!\n\n");
		p2_precedence = 4;
	}
	else if (is_straight(player2_hand, size))
	{
		printf("Straight!\n\n");
		p2_precedence = 6;
	}
	else if (is_three_of_a_kind(player2_hand, size))
	{
		printf("Three of a Kind!\n\n");
		p2_precedence = 7;
	}
	else if (is_two_pair(player2_hand, size))
	{
		printf("Two Pair!\n\n");
		p2_precedence = 8;
	}
	else if (is_pair(player2_hand, size))
	{
		printf("Pair!\n\n");
		p2_precedence = 9;
	}
	else
	{
		printf("High Card!\n\n");
		p2_precedence = 10;
	}

	if (p1_precedence == p2_precedence)
	{
		for (int i = 0; i < size; ++i)
		{
			++num_faces_p1[player1_hand.arr[i].face_index];
			++num_faces_p2[player2_hand.arr[i].face_index];
		}

		for (int i = 12; i > 0; --i)
		{
			if (num_faces_p1[i] > num_faces_p2[i])
			{
				winner = 1;
				i = 0;
			}
			else if (num_faces_p1[i] < num_faces_p2[i])
			{
				winner = 2;
				i = 0;
			}
		}
		if (num_faces_p1[0] > num_faces_p2[0])
		{
			winner = 1;
		}
		if (num_faces_p1[0] < num_faces_p2[0])
		{
			winner = 2;
		}
	}
	else if (p1_precedence < p2_precedence)
	{
		winner = 1;
	}
	else if (p1_precedence > p2_precedence)
	{
		winner = 2;
	}

	return winner;
}

void print_current_best_hand(Hand player_hand, int size)
{
	if (is_royal_flush(player_hand, 5))
	{
		printf("\n\nYou have a Royal Flush\n");
	}
	else if (is_straight(player_hand, 5) && is_flush(player_hand, 5))
	{
		printf("\n\nYou have a Straight Flush\n");
	}
	else if (is_four_of_a_kind(player_hand, 5))
	{
		printf("\n\nYou have a Four of a Kind\n");
	}
	else if (is_full_house(player_hand, 5))
	{
		printf("\n\nYou have a Full House\n");
	}
	else if (is_flush(player_hand, 5))
	{
		printf("\n\nYou have a Flush\n");
	}
	else if (is_straight(player_hand, 5))
	{
		printf("\n\nYou have a Straight\n");
	}
	else if (is_three_of_a_kind(player_hand, 5))
	{
		printf("\n\nYou have a Three of a Kind\n");
	}
	else if (is_two_pair(player_hand, 5))
	{
		printf("\n\nYou have a Two Pair\n");
	}
	else if (is_pair(player_hand, 5))
	{
		printf("\n\nYou have a Pair\n");
	}
	else
	{
		printf("\n\nYou have a High Card\n");
	}
}

int menu(void)
{
	int input = 0;
	do
	{
		printf("***Welcome to 5-Card Draw Poker***\n\n");
		printf("1. Game Rules\n2. Play Game\n3. Exit\n\n");
		scanf("%d", &input);
		if (input < 1 || input > 3)
		{
			printf("\nInvalid Input\n");
		}

	} while (input < 1 || input > 3);

	rewind(stdin);

	return input;
}

int get_bet(int style)
{
	char bet_input[9] = { '\0' };
	int amount = 0,
		length = 0,
		places_flag = 0;

	do
	{
		amount = 0;
		if (style == 1)
		{
			printf("What will be your initial bet? $");
		}
		else
		{
			printf("By how much will you raise your bet? $");
		}
		fgets(bet_input, 9, stdin);
		rewind(stdin);

		length = strlen(bet_input);

		places_flag = 0;
		for (int i = 0,j = 0, dec_flag = 0; bet_input[i] != '\n' && amount != -1; ++i)
		{
			
			if ((bet_input[i] == '.' || bet_input[i] == ',') && dec_flag == 0)
			{
				++dec_flag;
				amount /= 10;
			}
			else if (!isdigit(bet_input[i]))
			{
				printf("\n\nInvalid Input\n\n");
				amount = -1;
			}
			else
			{
				amount += (bet_input[i] - '1' + 1) * pow(10, length - j - 2 - dec_flag);

				if (dec_flag != 0)
				{
					++places_flag;
				}
				
				if (places_flag > 2)
				{
					printf("\n\nInvalid Input\n\n");
					amount = -1;
				}

				++j;
			
			}

			
		}

	} while (amount == -1);

	if (places_flag == 1)
	{
		amount *= 10;
	}
	else if (places_flag == 0)
	{
		amount *= 100;
	}

	return amount;
}