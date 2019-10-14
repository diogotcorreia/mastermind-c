#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void print_board();

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
  print_board();
}

void print_board()
{
  printf(" ?  ?  ?  ? \n");
  int i, k;
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
        printf(" %s%c" ANSI_COLOR_RESET, color_codes[rounds[i][k]], color_names[rounds[i][k]][0]);
        break;
      }
    }
    printf("\n");
  }
}