#include "stm32l1xx_nucleo.h"
#include "../includes/displayLCD.h"
#include <stdarg.h>
#include <stdio.h>


void GPIO_init(void)
{
  /* Enable clock PORT A */
   //RCC->AHBENR |= (1<<0);
   RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  
   /****** Config GPIO for SPI1 ******/
  
  /* Set PA5 (SPI clock), PA7 (MOSI) in Alternate Function Push Pull*/
   
   //GPIOA->MODER |= (1<<11) | (1<<15);
   GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER7_1;
   //GPIOA->OTYPER &= ~((1<<5) | (1<<7));   
   GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_7);
   
  /* Connect AF to SPI1 */
   GPIOA->AFR[0] |= (1<<20) | (1<<22);
   GPIOA->AFR[0] |= (1<<28) | (1<<30);
   
  /* Set PA8 in output push pull to manage CS */
   // GPIOA->MODER |= (1<<16);
   GPIOA->MODER |= GPIO_MODER_MODER8_0;
   //GPIOA->OTYPER &= ~(1<<8);
   GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_8);
}

void SPI_Config(void)
{
  
   /* Enable clock SPI1*/
   // RCC->APB2ENR |= (1<<12);
   RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
   
   /* Select BR[2:0] to set serial clock baud rate */
   /* Set fpclk/8*/
   SPI1->CR1 |= SPI_CR1_BR_1;
       
   /* Select the CPOL and CPHA bits */
   SPI1->CR1 &= ~(SPI_CR1_CPHA | SPI_CR1_CPOL);

   /* Set SPI in Master mode (bit MSTR)*/
   SPI1->CR1 |= SPI_CR1_MSTR;
  
  /* Set the DFF bit to define 8- or 16-bit data frame format */
   SPI1->CR1 &= ~ SPI_CR1_DFF;  //8 bit
     
  /* Configure the LSBFIRST bit for MSB transmitted first ( set to 0)*/
  SPI1->CR1 &= ~ SPI_CR1_LSBFIRST;
     
  /* Set BIDIMODE=1, BIDIOE=1 : 1 clock and 1 line in bidirectional data wire (BIDIMODE=1)
      BIDIOE bit is 1, the data line is output */
   SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
        
  /* Hardware NSS 'chip select) management (SSOE = 1) */
   //SPI1->CR2 |= (1<<2);
   SPI1->CR2 |= SPI_CR2_SSOE;
      
  /* Enable SPI */
   //SPI1->CR1 |= (1<<6);
   SPI1->CR1 |= SPI_CR1_SPE;
 }

void Set_CS()
{
GPIOA->ODR |= (1<<8);
}

void Reset_CS()
{
GPIOA->ODR &= ~(1<<8);
}

void SendData_SPI(uint8_t data)
{
 /* Wait while Tx buffer is not empty to write new data */
 //while ( (SPI1->SR & (1<<1)) != (1<<1));
 while ( (SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE);
 SPI1->DR =data; // the data is in the data register of SP1
}

void SPI_write(uint8_t add, uint8_t data)
{
Set_CS();
Reset_CS(); // the Max 7219 is selected
SendData_SPI(add);
SendData_SPI(data);
//while ((SPI1->SR & (1<<7)) == (1<<7));
while ((SPI1->SR & SPI_SR_BSY) == SPI_SR_BSY);
Set_CS();
}
void Delay(uint32_t Tempo)
{
while(Tempo--);
}

void initLCD(DISPLAYLCD* DisplayLcd){

  GPIO_init();
  SPI_Config();
  
   /* Max 7219 configuration */  
  
  //Addresse registre, valeur)//
  
  //SPI_write(0x0C, 0x01); // 1 => Normal Operation / 0 => Shutdown mode  //ON / OFF
  //SPI_write(0x0A, 0x0F); // Intensity 
  //SPI_write(0x09, 0x0F); // Code B decode ////////////////::
  SPI_write(0x09, 0x00); // No decode
  
  SPI_write(0x0B, 0x03); // Scan-limit Format : number of active digits (table8 of data sheet)
  SPI_write(0x0F, 0x00); // Display test mode off ( normal display)
  

  for (int i=0; i<4; i++){
    
    DisplayLcd->digit[i].id = i+1;    
    DisplayDigit(DisplayLcd, i+1, EMPTY);
    
  }
 
}

void IntensityLCD(DISPLAYLCD* DisplayLcd, uint8_t intensity){
  
         SPI_write(0x0A, intensity);
         DisplayLcd->intensity = intensity;
}

void statusLCD(DISPLAYLCD* DisplayLcd, Mode etat){

  SPI_write(0x0C, etat);
  DisplayLcd->mode = etat;

}

void DisplayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t val){

  SPI_write(id, val);
  DisplayLcd->digit[id-1].val= val;

}

void createDigit(uint8_t* current, int n, ...){
  
    *current = 0;
    uint8_t a;
  
    uint8_t digit[N];
 
    digit[0]=R0;
    digit[1]=R1;
    digit[2]=L0;
    digit[3]=L1; 
    digit[4]=M0;
    digit[5]=M1;
    digit[6]=M2;
    digit[7]=P0;

    va_list valist;
    va_start(valist,n);
  
    for (int i=0; i<n;i++){             //nb args
      a = va_arg(valist, int);
      
      for (int j=0; j<N; j++){
        
          if( digit[j] ==  a ){
              (*current) |=  digit[j];   
          }     
      }
    }
    
   va_end(valist);
}


void printfDigit(DISPLAYLCD* DisplayLcd,char* text, Speed speed){
  
  char* c;
  char* ptr;
  int i=1;
  
  c = text;
  ptr = text;
  
  while(*c != '\0'){
        
    printDigit(DisplayLcd,i, *c); 
    c++;
    i++;
       
    if(i == 5 && *c != '\0'){
      ptr++;
      c=ptr;
      i=1;
      Delay(speed);

    }
  
  }
  
  DisplayDigit(DisplayLcd, i, EMPTY);
  
}


void printDigit(DISPLAYLCD* DisplayLcd,int id, char c){

  uint8_t alphabet[DICO][2] ={   {'A', 0b01110111},
                                {'B', 0b00011111},
                                {'C', 0b01001110},
                                {'D', 0b00111101},
                                {'E', 0b01001111},
                                {'F', 0b01000111},                                                      
                                {'G', 0b01011110},
                                {'H', 0b00010111},                               
                                {'I', 0b00000110},
                                {'J', 0b00111100},
                                {'K', 0b01010111},
                                {'L', 0b00001110},
                                {'M', 0b01010100},
                                {'N', 0b01110110},
                                {'O', 0b01111110},
                                {'P', 0b01100111},
                                {'Q', 0b01110011},
                                {'R', 0b01010110},
                                {'S', 0b01011011},
                                {'T', 0b00001111},
                                {'U', 0b00111110},
                                {'V', 0b00111010},
                                {'W', 0b00101010},
                                {'X', 0b00110111},
                                {'Y', 0b00111011},
                                {'Z', 0b01101001},
                                {'0', 0b01111110},      //number
                                {'1', 0b00110000},
                                {'2', 0b01101101},
                                {'3', 0b01111001},
                                {'4', 0b00110011},
                                {'5', 0b01011011},
                                {'6', 0b01011111},
                                {'7', 0b01110000},
                                {'8', 0b01111111},
                                {'9', 0b01111011},
                                {' ', 0b00000000},      //Ponctuation
                                {'.', 0b10000000},
                                {'!', 0b10100000},
                              
                         };
  int find = 0;

  for(int i =0; i<DICO+1;i++){
  
    if(alphabet[i][0] == c){    
      
      DisplayDigit(DisplayLcd, id, alphabet[i][1]);
      find = 1;
    } 
  }  
    if(find == 0)
      DisplayDigit(DisplayLcd, id, 0b10000000);
}

/*      
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
                              
   */                           
 
void blinkingLCD( DISPLAYLCD* DisplayLcd, Speed speed ){
  
  for(int i=0; i<2;i++){
  
  IntensityLCD(DisplayLcd,0);  //Between 0 to 15
  Delay(speed);
  IntensityLCD(DisplayLcd,15);  //Between 0 to 15
  Delay(speed);
  IntensityLCD(DisplayLcd,0);  //Between 0 to 15
  
  }
  
}

void printIntDigit(DISPLAYLCD* DisplayLcd,int number, Speed speed){
  
     char text[CHAR_TEXT_MAX];
     
     sprintf(text, "%d",  number);
     printfDigit(DisplayLcd,text, speed); 
}


void eraseLCD(DISPLAYLCD* DisplayLcd){

  for (int i=1; i<5;i++){
  
    DisplayDigit(DisplayLcd, i, EMPTY);
  
  }

}