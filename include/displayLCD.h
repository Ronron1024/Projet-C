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
void Delay(uint32_t);

//mode ON/OFF pour le lcd
void statusLCD(DISPLAYLCD* DisplayLcd, Mode mode);

//Reglage de l' intensité du lcd, entre 0 et 15
void IntensityLCD(DISPLAYLCD* DisplayLcd, uint8_t intensity);

//Affiche "val" sur le digit "id"
void DisplayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t val);

//genere un tableau constité des n segments à afficher
void  ArrayDigit(uint8_t array[N], int n, ...);

//Affiche le tableau de segment sur le digit 'id'
void DisplayArrayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t array[N]);

//Pour initialiser un tableau à 0
void initArray(uint8_t* array,int n);