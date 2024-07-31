#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();

    DL_TimerA_startCounter(PWM_0_INST);

    while (1)
    {
        if (DL_GPIO_readPins(GPIO_LEDS_SWITCH_1_PORT, GPIO_LEDS_SWITCH_1_PIN))
        {
            printf("Duty cycle changed\n");
            DL_TimerA_setCaptureCompareValue(PWM_0_INST, 7500, GPIO_PWM_0_C0_IDX);
        }

        if (DL_GPIO_readPins(GPIO_LEDS_PIN_24_PORT, GPIO_LEDS_PIN_24_PIN))
        {
            DL_GPIO_setPins(GPIO_LEDS_LED_PORT, GPIO_LEDS_LED_PIN);
        }
        else
        {
            DL_GPIO_clearPins(GPIO_LEDS_LED_PORT, GPIO_LEDS_LED_PIN);
        }
    }
}
