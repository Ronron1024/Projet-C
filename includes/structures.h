#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <time.h>

typedef struct {
  
  uint8_t id;           //id digit, 1 to 4
  uint8_t val;          //for display

} DIGIT;

typedef struct {
  
  int mode;            //status ON/OFF
  int intensity;        //Between 0, 15
  DIGIT digit[4];         
  
} DISPLAYLCD;

typedef struct {
  
    uint8_t id;
    int status;           //1 pressed - 0 not pressed
    //clock_t start;
    //uint32_t duration;   //duration (s) of the current status pressed
    uint32_t count;      //count of button is pressed and relaxed

} BTN;

#endif