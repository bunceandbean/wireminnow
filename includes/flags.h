#ifndef FLAGS_H
#define FLAGS_H

/*********************/ // CONSTANTS

#define MINIMUM_ARGS 2
#define MAXIMUM_ARGS 16

// Flag indexes
enum flag_idx {
    IP_USE_NAME,
};

/*********************/

/*********************/ // FUNCTIONS

void process_arguments(char **, int);

int check_flag(enum flag_idx);

/*********************/



#endif