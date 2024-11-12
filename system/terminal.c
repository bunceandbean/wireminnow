#include "wireminnow.h"

/*
    Print n bytes of an unsigned char *, while potentially outputting printable characters.
*/
void print_bytes(unsigned char * mem, int n, int char_out, char end_char) {
  for (int i = 0; i < n; i++) {
    printf((char_out && mem[i] >= 33 && mem[i] <= 126) ? ("%c%c") : ("%02X%c"), mem[i], (i != n-1) ? ' ' : end_char);
  }
}

/*
    Prints out fun wireminnow fish.
*/
void print_fish() {
    printf(FISH_ART, BLUE_OUT, RED_OUT, BLUE_OUT, NO_COLOR);
}

