#include "stm32l1xx_nucleo.h"
#include "../includes/buttons.h"
  
void initButton(BTN* btn, int num){
  
  btn->id = num;
  btn->status = 0;
  //btn->duration = 0;
  btn->count = 0; 
   
} 
  
void initButtons(BTN* btn1, BTN* btn2, BTN* btn3, BTN* btn4 ){
 
  initButton(btn1, 1);
  initButton(btn2, 2);
  initButton(btn3, 3);
  initButton(btn4, 4);
  
}

void enable_interrupt_ext_buttons(void){

   RCC->APB2ENR |= (1<<0);             //SysConfig genere l'interuption sur la ligne
   
   
   
  //En fonction du type de l' interruption - Activation de l' interuption
   NVIC->ISER[1] |=(1<<8);             /*EXTI15_10_IRQn : 40 table des vecteurs*/
   
   //Bouton sur PA11
   EXTI->IMR |= (1<<11);    //Bouton sur PA11 => EXT11
   EXTI->FTSR |= (1<<11);   //Front descendant
   EXTI->RTSR |= (1<<11);   //Front montant
   
   SYSCFG->EXTICR[2]&= ~(1<<12);        //Config PA
   SYSCFG->EXTICR[2]&= ~(1<<13);
   SYSCFG->EXTICR[2]&= ~(1<<14);
   SYSCFG->EXTICR[2]&= ~(1<<15);
   
   //Bouton sur PA12
   EXTI->IMR |= (1<<12);
   EXTI->FTSR |= (1<<12);  //Front descendant
   EXTI->RTSR |= (1<<12);   //Front montant
   
   SYSCFG->EXTICR[3]&= ~(1<<0);
   SYSCFG->EXTICR[3]&= ~(1<<1);
   SYSCFG->EXTICR[3]&= ~(1<<2);
   SYSCFG->EXTICR[3]&= ~(1<<3);
   
   
  //En fonction du type de l' interruption
   NVIC->ISER[0] |= (1<<23);    /* EXTI9_5_IRQn: 23 table des vecteurs*/
   
   //Bouton sur PC6
   EXTI->IMR |= (1<<6);
   EXTI->FTSR |= (1<<6);  //Front descendant
   EXTI->RTSR |= (1<<6);   //Front montant
   
   SYSCFG->EXTICR[1]&= ~(1<<8);         //Config PC
   SYSCFG->EXTICR[1]|=  (1<<9);
   SYSCFG->EXTICR[1]&= ~(1<<10);
   SYSCFG->EXTICR[1]&= ~(1<<11);
   
   //Bouton sur PC5
   EXTI->IMR |= (1<<5);
   EXTI->FTSR |= (1<<5);  //Front descendant
   EXTI->RTSR |= (1<<5);   //Front montant
   
   SYSCFG->EXTICR[1]&= ~(1<<4);
   SYSCFG->EXTICR[1]|=  (1<<5);
   SYSCFG->EXTICR[1]&= ~(1<<6);
   SYSCFG->EXTICR[1]&= ~(1<<7);

}