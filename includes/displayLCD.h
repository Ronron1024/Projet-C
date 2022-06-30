#include "structures.h"
#include "define.h"

//Init structure DISPLAYLCD et init configuration SPI
void initLCD(DISPLAYLCD* DisplayLcd);
void GPIO_init(void);
void Set_CS();
void Reset_CS();
void SPI_Config(void);
void SendData_SPI(uint8_t data);
void SPI_write(uint8_t add, uint8_t data);
int Delay(uint32_t);

//mode ON/OFF pour le lcd
void statusLCD(DISPLAYLCD* DisplayLcd, Mode mode);

//Reglage de l' intensité du lcd, entre 0 et 15
void IntensityLCD(DISPLAYLCD* DisplayLcd, uint8_t intensity);

//Affiche "val" sur le digit "id"
void DisplayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t val);

//creer la valeur current, equivalente au choix des segments à afficher (liste des segments dans le define.h)
void createDigit(uint8_t* current, int n, ...);

//Basculment de l' intensité du LCD de mini, à max et retour à mini, à intervalle de temps parametrable
void blinkingLCD(DISPLAYLCD* DisplayLcd, Speed speed);

//Affiche sur le LCD une chaine de caractere, avec une vitesse de defilement parametrable
void printfDigit(DISPLAYLCD* DisplayLcd,char* text, Speed speed);
////Affiche un caractere sur le digit id du LCD
void printDigit(DISPLAYLCD* DisplayLcd,int id, char c);
//Affiche sur le LCD une variable de type int, avec une vitesse de defilement parametrable
void printIntDigit(DISPLAYLCD* DisplayLcd,int number, Speed speed);
//Efface les 4 digits
void eraseLCD(DISPLAYLCD* DisplayLcd);