#include <stdint.h>
#include "stm32f0xx.h"
#include "sct.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{
	sct_init();
	sct_led(0x7A5C36DE);


	while (1) {
		for(uint32_t i = 0; i<999; i+=111){
			sct_value(i);
			for (volatile uint32_t ii = 0; ii < 100000; ii++) {}
		}

	}
}



