#ifndef TERMINAL_H
#define TERMINAL_H

/*********************/ // CONSTANTS
#define LIST_INDENT "   > "
#define BLUE_OUT "\033[0;36m"
#define RED_OUT "\033[0;31m"
#define NO_COLOR "\033[0m"
#define FISH "><((('>"
#define FISH_SPACE "       "
#define WELCOME  "%s\n//==================================================================================\\\\\n||        %s                                               %s             ||\n||                                                  %s                         ||\n||                                    %sWIREMINNOW%s                                    ||\n||                                                                                  ||\n||             %s                                  %s                     ||\n\\\\==================================================================================//\n\n%s"
/*********************/


/*********************/ // FUNCTIONS

void print_bytes(unsigned char *, int, int, char);
void print_fish();
char * get_fish();

/*********************/




#endif