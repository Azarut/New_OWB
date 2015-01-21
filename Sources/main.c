/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
#include "stm32f4xx_conf.h"                      // RTOS object definitions
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "Step_Driver.h" 

GPIO_InitTypeDef  GPIO_InitStructure;
/*
 * main: initialize and start the system
 */
void BlinkThread (void const *argument)
 {
	while(1)
	{
    rotate = 100;
		osDelay(1000);
	}
 }
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
  // initialize peripherals here
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
	InitializeTimer();

	// create 'thread' functions that start executing,BlinkThread 
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	tid_BlinkThread  = osThreadCreate (osThread(BlinkThread ), NULL);
	osKernelStart ();                         // start thread execution 
	while(1)
	{
	}
}
