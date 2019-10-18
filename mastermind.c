#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define SEQUENCE_LENGTH 4
#define ROUNDS 12

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

#define COLOR_AMOUNT 6
const char *color_names[COLOR_AMOUNT] = {"Red", "Green", "Yellow", "Blue", "Magenta", "Cyan"};
const char *color_codes[COLOR_AMOUNT] = {"\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m"};

int sequence[SEQUENCE_LENGTH];
int rounds[ROUNDS][SEQUENCE_LENGTH];

void generate_sequence();
void play_round();
void print_board(bool end);
void print_clues(int round);
void wait_for_guess();
int get_color_index(char color);

// Setup game
int main()
{
  // Use current time as
  // seed for random generator
  srand(time(0));

  generate_sequence();

  //TODO remove after debugging
  printf("%d %d %d %d\n", sequence[0], sequence[1], sequence[2], sequence[3]);

  // Fill 'rounds' variable
  int i, k;
  for (i = 0; i < ROUNDS; i++)
    for (k = 0; k < SEQUENCE_LENGTH; k++)
      rounds[i][k] = -1;

  play_round();

  return 0;
}

void generate_sequence()
{
  int i;
  for (i = 0; i < SEQUENCE_LENGTH; i++)
    sequence[i] = (rand() % (COLOR_AMOUNT));
}

void play_round()
{
  int round;
  for (round = 0; round < ROUNDS; round++)
  {
    print_board(false);
    wait_for_guess(round);
  }
  print_board(true);
}

void print_board(bool end)
{
  int i, k;

  // Choose whether to display ? or the actual correct sequence
  if (end)
    for (k = 0; k < SEQUENCE_LENGTH; k++)
      printf(" %s%c " ANSI_COLOR_RESET, color_codes[sequence[k]], color_names[sequence[k]][0]);
  else
    for (k = 0; k < SEQUENCE_LENGTH; k++)
      printf(" ? ");
  printf("\n");

  // Print the board
  for (i = 0; i < ROUNDS; i++)
  {
    for (k = 0; k < SEQUENCE_LENGTH; k++)
    {
      switch (rounds[i][k])
      {
      case -1:
        printf(" . ");
        break;
      default:
        printf(" %s%c " ANSI_COLOR_RESET, color_codes[rounds[i][k]], color_names[rounds[i][k]][0]);
        break;
      }
    }
    print_clues(i);
    printf("\n");
  }

  if (end)
    return;
  // Print instructions

  printf("Available colors:");
  for (k = 0; k < COLOR_AMOUNT; k++)
    printf(" %s%s" ANSI_COLOR_RESET, color_codes[k], color_names[k]);
  printf("\nType the first letter of the color in a sequence. Example: RGYC\n");
}

void print_clues(int round)
{
  int i, clues_available[SEQUENCE_LENGTH];
  // Clone correct sequence
  for (i = 0; i < SEQUENCE_LENGTH; i++)
  {
    if (rounds[round][i] == sequence[i])
    {
      printf(ANSI_COLOR_GREEN "+" ANSI_COLOR_RESET);
      clues_available[i] = -2; // Set to -2 so we can ignore it afterwards
      continue;
    }
    clues_available[i] = sequence[i];
  }

  int k;
  for (i = 0; i < SEQUENCE_LENGTH; i++)
  {
    if (clues_available[i] == -2)
      continue;
    for (k = 0; k < SEQUENCE_LENGTH; k++)
      if (rounds[round][i] == clues_available[k])
      {
        printf(ANSI_COLOR_RED "-" ANSI_COLOR_RESET);
        clues_available[k] = -1;
        break;
      }
  }
}

void wait_for_guess(int round)
{
  char guess[SEQUENCE_LENGTH + 10]; // add a buffer for wrong inputs
  printf("Your guess: ");
  scanf("%s", guess);
  printf("%s\n", guess);
  int i, guess_array[SEQUENCE_LENGTH];
  for (i = 0; i < SEQUENCE_LENGTH; i++)
  {
    int color_index = get_color_index(guess[i]);
    if (color_index == -1)
    {
      if (guess[i] == 0)
        printf("The sequence must have %d colors. Please try again.\n", SEQUENCE_LENGTH);
      else
        printf("Color %c not found. Please try again.\n", guess[i]);
      wait_for_guess(round);
      return;
    }
    guess_array[i] = color_index;
  }
  for (i = 0; i < SEQUENCE_LENGTH; i++)
    rounds[round][i] = guess_array[i];
}

int get_color_index(char color)
{
  int i;
  for (i = 0; i < COLOR_AMOUNT; i++)
    if (toupper(color) == color_names[i][0])
      return i;
  return -1;
}