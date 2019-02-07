#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_rcc.h>

#include <stm32l4xx_ll_gpio.h>

int main(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
    
    while (1) {
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_7);
    }
}
