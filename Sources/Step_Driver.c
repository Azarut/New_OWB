
#include "Step_Driver.h" 


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 100;
uint16_t CCR2_Val = 300;
uint16_t CCR3_Val = 300;
uint16_t CCR4_Val = 300;
uint16_t PrescalerValue = 0;

uint8_t  state = 1;
uint8_t  rotate = 0;
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		switch (state)
		{
			case 1:
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_10);
						GPIO_ResetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 2:
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
						GPIO_SetBits(GPIOA, GPIO_Pin_15);
						GPIO_ResetBits(GPIOA, GPIO_Pin_10);
						GPIO_ResetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 3:
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
						GPIO_SetBits(GPIOA, GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_10);
						GPIO_ResetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 4:
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
						GPIO_SetBits(GPIOA, GPIO_Pin_15);
						GPIO_SetBits(GPIOB, GPIO_Pin_10);
						GPIO_ResetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 5:
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_15);
						GPIO_SetBits(GPIOB, GPIO_Pin_10);
						GPIO_ResetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 6:
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_15);
						GPIO_SetBits(GPIOB, GPIO_Pin_10);
						GPIO_SetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 7:
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_10);
						GPIO_SetBits(GPIOB, GPIO_Pin_3);
						state++;
			break;
			case 8:
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
						GPIO_ResetBits(GPIOA, GPIO_Pin_15);
						GPIO_ResetBits(GPIOB, GPIO_Pin_10);
						GPIO_SetBits(GPIOB, GPIO_Pin_3);
						state = 1;
						//rotate --;
			break;			
		
	}
	}
}
void InitializeTimer(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOC and GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

  /* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_15 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* GPIOB Configuration:  TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 |GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 10000;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  

	  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	
	TIM_Cmd(TIM3, ENABLE);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
}

