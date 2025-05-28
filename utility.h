#ifndef UTILITY_H
#define UTILITY_H

#define check_null(x) if ((x) == NULL) {fprintf(stderr, "NullPTR: %d",  __LINE__); exit(EXIT_FAILURE);}

void print_time();

#endif
