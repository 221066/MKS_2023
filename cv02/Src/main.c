#include <stdint.h>
#include "stm32f030x8.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


// Start: CTRL+B, F11 -> spustenie programu a nahranie

//
volatile uint32_t Tick=0;

// Symbol definitions
#define LED_TIME_BLINK 500 //500 ms
#define LED_TIME_SHORT 300 //100 ms
#define LED_TIME_LONG 1000 //1000 ms

// Function declarations
void blikac(void);
void tlacitka(void);

void SysTick_Handler(void)
 {
	Tick++;
 }

int main(void)
{
	//init SysTick timer
	SysTick_Config(8000); // 1ms

	RCC->AHBENR   |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN; // enable
	GPIOA->MODER  |= GPIO_MODER_MODER4_0; // LED1 = PA4, output
	GPIOB->MODER  |= GPIO_MODER_MODER0_0; // LED2 = PB0, output
	GPIOC->PUPDR  |= GPIO_PUPDR_PUPDR0_0; // S2 = PC0, pullup
	GPIOC->PUPDR  |= GPIO_PUPDR_PUPDR1_0; // S1 = PC1, pullup

	//Clock SYSCFG povolenie
	RCC->APB2ENR      |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC; // select PC0 for EXTI0
	EXTI->IMR         |= EXTI_IMR_MR0; 			  // mask
	EXTI->FTSR        |= EXTI_FTSR_TR0;           // trigger on falling edge
	//NVIC_EnableIRQ(EXTI0_1_IRQn);                 // enable EXTI0_1


	/* Loop forever */
	for (;;) {
		blikac();
		tlacitka();
	}

}


// LED blinking
void blikac(void)
 {
	static uint32_t delay;

	if (Tick > delay + LED_TIME_BLINK) {
		GPIOA->ODR ^= GPIO_ODR_4;                //negacia PA4/LED1;
		delay = Tick;
	}
 }


// Button press and LED 2 timer
void tlacitka(void)
{
	static uint32_t delay5;
	static uint32_t delay40;
	static uint32_t old_s2;
	//static uint32_t old_s1;
	static uint32_t off_time;

	uint32_t new_s2 = GPIOC->IDR & (1<<0);		//Button s2
	//uint32_t new_s1 = GPIOC->IDR & (1<<1);	//Button s1

	//Button s2
	if (Tick > delay40 +40) {
		if (old_s2 && !new_s2) { // falling edge
			off_time = Tick + LED_TIME_SHORT;
			GPIOB->BSRR = (1<<0);
		 }
		 old_s2 = new_s2;
		 delay40 = Tick;

	}

	//Button s1
	if (Tick > delay5 + 5) {
		static uint16_t debounce = 0xFFFF;
		debounce <<= 1;
		if (GPIOC->IDR & (1<<1)) debounce |= 0x0001;
		if (debounce == 0x8000){
			off_time = Tick + LED_TIME_LONG;
			GPIOB->BSRR = (1<<0); //LED2
		}
		delay5 = Tick;
	}


	/*
	if (old_s1 && !new_s1) { // falling edge
		off_time = Tick + LED_TIME_LONG;
		GPIOB->BSRR = (1<<0); //LED2
	}
	old_s1 = new_s1;
	*/

	if (Tick > off_time) {
		GPIOB->BRR = (1<<0);
	}


}

 void EXTI0_1_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR0) { // check line 0 has triggered the IT
		EXTI->PR |= EXTI_PR_PR0; // clear the pending bit
		GPIOB->ODR ^= GPIO_ODR_0; //negation PB0
	}
}

