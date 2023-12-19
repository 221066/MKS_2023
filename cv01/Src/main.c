#include <stdint.h>

#include "stm32f030x8.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
	uint32_t sos_msg = 0b10101001110111011100101010000000; // SOS Message

	// GPIO init
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;

	// Infinite loop
	while (1) {
		for (uint8_t ind = 0; ind < 32; ind++)
		{
			if (sos_msg & (1UL <<ind)) {
				GPIOA->BSRR = (1<<5); // ON
			} else {
				GPIOA->BRR = (1<<5); // OF
			}

			for (volatile uint32_t i = 0; i < 100000; i++) {} // wait
		}
	}

}
