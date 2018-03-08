#ifndef _PRINT_H_
#define _PRINT_H_


#define BLUE "\033[0;32;24m"
#define RED "\033[0;31;24m"
#define NONE "\033[0m"
#define DEPBLUE "\033[0;34;24m"
#define CLEAR() printf("\033[2J")

#define MOVETO(x,y) printf("\033[%d;%dH", (y), (x))

#endif
