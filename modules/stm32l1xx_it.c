/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    16-May-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "structures.h"
#include "displayLCD.h"  

extern  BTN button1;
extern  BTN button2;
extern  BTN button3;
extern  BTN button4;
 
 void EXTI15_10_IRQHandler(){ /*Table vecteur logiciel => 40*/
                              /*system_stm32l1xx.h */
   //double calc;
   

   Delay(10000);        //evite "les micros rebonds"
   
   if (EXTI->PR & (1<<11)) //Lorqu' il y a interruption 
   {
     EXTI->PR |= (1<<11);
     if( button1.status == 1){
          button1.status = 0;
          button1.count += 1;
          //clock_t current = clock();         
          //calc = current - button1.start;
         // button1.duration= (uint32_t) calc*10;  //en milliseconde, 

          
     }
      else
        button1.status = 1;
        //button1.start = clock(); //Chrono ON
        
   }
   
  if (EXTI->PR & (1<<12))
   {
     EXTI->PR |= (1<<12);
     
     if( button2.status == 1){
          button2.status = 0;
          button2.count += 1;   
     }
      else
        button2.status = 1;
   }  
 }
  
 
 void EXTI9_5_IRQHandler (){  /*Table vecteur logiciel => 23*/
   
   Delay(10000);        //evite "les micros rebonds"
   
   if( EXTI->PR & (1<<6) ) {   
     EXTI->PR |= (1<<6);
     
     if( button3.status == 1){
      button3.status = 0;
      button3.count += 1;   
     }
     else
      button3.status = 1; 
   }
     
   if( EXTI->PR & (1<<5) ){   
     EXTI->PR |= (1<<5);
     
     if( button4.status == 1){
      button4.status = 0;
      button4.count += 1;   
     }
     else
      button4.status = 1; 
     
   } 
 }
 
 


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
    
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/






/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
