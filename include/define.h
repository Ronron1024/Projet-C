typedef int Mode;
#define OFF 0
#define ON 1

//Number of segment on digit
#define N 8

//segment digit defintion
#define R0 0b00010000   //on the right, lower
#define R1 0b00100000
#define L0 0b00000100   //on the left, lower
#define L1 0b00000010
#define M0 0b00001000   //on the middle, lower
#define M1 0b00000001
#define M2 0b01000000
#define P0 0b10000000   //point
#define EMPTY 0b00000000