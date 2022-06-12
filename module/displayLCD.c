#include "stm32l1xx_nucleo.h"
#include "displayLCD.h"
#include <stdarg.h>


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


//0 entre 15
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


void DisplayArrayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t array[N]){

  uint8_t val;
  uint8_t digit[N];
 
  digit[0]=R0;
  digit[1]=R1;
  digit[2]=L0;
  digit[3]=L1; 
  digit[4]=M0;
  digit[5]=M1;
  digit[6]=M2;
  digit[7]=P0;

  for(int i=0; i<N; i++){
  
    if(array[i] == 1 ){   
      val |=  digit[i];
    }  
  }

  SPI_write(id, val);
  DisplayLcd->digit[id-1].val= val;

}


void  ArrayDigit(uint8_t array[N], int n, ...){
//void  ArrayDigit(uint8_t array[N], uint8_t n){
  
    uint8_t digit[N];
 
    digit[0]=R0;
    digit[1]=R1;
    digit[2]=L0;
    digit[3]=L1; 
    digit[4]=M0;
    digit[5]=M1;
    digit[6]=M2;
    digit[7]=P0;
    
    initArray(array,N);
    
    va_list valist;
    va_start(valist,n);
  
    for (int i=0; i<n;i++){
      uint8_t a = va_arg(valist, uint8_t);
      
      for (int j=0; j<N; j++){
        
          if( digit[j] ==  a ){
            array[j] = 1;    
          }     
      }
    }
    
   va_end(valist);
}


void initArray(uint8_t* array,int n){

  for(int i=0; i<n;i++){
    
    array[i]=0;   
  }
}

