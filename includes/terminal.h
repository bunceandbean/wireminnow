#ifndef TERMINAL_H
#define TERMINAL_H

/*********************/ // CONSTANTS
#define LIST_INDENT "   > "
#define BLUE_OUT "\033[0;36m"
#define RED_OUT "\033[0;31m"
#define NO_COLOR "\033[0m"
#define FISH_ART  "%s\n           FISHKISSFISHKIS\n       SFISHKISSFISHKISSFISH            F\n    ISHK   ISSFISHKISSFISHKISS         FI\n  SHKISS   FISHKISSFISHKISSFISS       FIS\nHKISSFISHKISSWIREMINNOWFISHFIFISH    KISS\n  FISHKISSFISHKISSFISHKISSFISHKISS  FISHK\n      SSFISHK%sWIREMINNOW%sISSFHKISSFISHKISSF\n  ISHKISSFISHKISSFISHKISSFISHKISSF  ISHKI\nSSFISHKISSFISHKISSFISHKISSFISHKIS    SFIS\n  HKISSWIREMINNOWSHKISSFISHKISS       FIS\n    HKISSFISHKISSFISHKISSFISHK         IS\n       SFISHKISWIREMINNOWFIS            K\n         ISSFISHKISSFISHK               \n\n%s"
/*********************/


/*********************/ // FUNCTIONS

void print_bytes(unsigned char *, int, int, char);
void print_fish();

/*********************/




#endif