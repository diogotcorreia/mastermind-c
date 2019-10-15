#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SEQUENCE_LENGTH 4
#define ROUNDS 12

#define ANSI_COLOR_RESET "\x1b[0m"

#define COLOR_AMOUNT 6
const char *color_names[COLOR_AMOUNT] = {"Red", "Green", "Yellow", "Blue", "Magenta", "Cyan"};
const char *color_codes[COLOR_AMOUNT] = {"\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m"};

int sequence[SEQUENCE_LENGTH];
int rounds[ROUNDS][SEQUENCE_LENGTH];

void generate_sequence();
void play_round();
void print_board(bool end);
void wait_for_guess();

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
  print_board(false);
  wait_for_guess();
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

void wait_for_guess()
{
  char *guess[SEQUENCE_LENGTH];
  printf("Your guess: ");
  scanf("%s", guess);
  printf("%s\n", guess);
  // TODO
}