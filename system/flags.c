
#include "wireminnow.h"


char * flag_strings[] = {"-IP-use-names"};

unsigned short flags = 0x0000u;

/*
    Processes `n` arguments, setting the bits of unsigned short `flags` based off present flags.
*/
void process_arguments(char * args[], int n) {

    for (unsigned short i = 0; i < n; i++) {
        if (!strcmp(args[i], flag_strings[i])) flags = flags || (1u << i);
    }

}

/*
    Checks if flag is set at `idx`.
*/
int check_flag(enum flag_idx idx) {
    return flags & (1u << idx);
}