#include "wireminnow.h"

/*
    Print n bytes of an unsigned char *, while potentially outputting printable characters if `char_out`.
*/
void print_bytes(unsigned char * mem, int n, int char_out, char end_char) {
  for (int i = 0; i < n; i++) {
    printf((char_out && mem[i] >= 33 && mem[i] <= 126) ? ("%c%c") : ("%02X%c"), mem[i], (i != n-1) ? ' ' : end_char);
  }
}

/*
  Returns either a `FISH` or a `FISH_SPACE`
*/
char * get_fish() {
  return (rand() % 2) ? FISH : FISH_SPACE;
}

/*
    Prints out fun wireminnow fish.
*/
void print_fish() {
    printf(WELCOME, BLUE_OUT, get_fish(), get_fish(), get_fish(), RED_OUT, BLUE_OUT, get_fish(), get_fish(), NO_COLOR);
}

