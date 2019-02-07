#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_rcc.h>

#include <stm32l4xx_ll_gpio.h>
#include <stm32l4xx_ll_rcc.h>
#include <stm32l4xx_ll_system.h>

// Some of the examples like to do the clock initialization
// from the reset handler before calling main. I'm not sure
// what value it adds except ensuring it really is the first
// thing to be done. I did think the SYSCLK could be set
// before doing the C data initialization and then that would
// go faster.
static void sys_clk_init(void) {
    // Ensure the flash will still work after increasing
    // SYSCLK to 80 MHz.
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);

    // MSI will be enabled and running after reset as it is the default clock src.

    // Configure the PLL to generate the 80 MHz.
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(LL_RCC_PLL_IsReady() != 1) {
    };

    // Change SYSCLK source to PLL rather than MSI.
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    };
}

int main(void) {
    sys_clk_init();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
    
    while (1) {
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_7);
    }
}
