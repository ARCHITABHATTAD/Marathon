//single conversion vref internal
//vref- voltage reference

#include "ti_msp_dl_config.h"
#include "stdio.h"

volatile uint8_t flag =0;
volatile uint16_t result = 0;

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);


    while (1) {
        DL_ADC12_startConversion(ADC12_0_INST);
        if(flag == 0) {
            __WFI();
        }
        result = DL_ADC12_getMemResult(ADC12_0_INST, 0);
        printf("%d \n", result);
        DL_ADC12_disableConversions(ADC12_0_INST);
        flag = 0;
        DL_ADC12_enableConversions(ADC12_0_INST);
    }
}

void ADC12_0_INST_IRQHandler(void) {
    switch(DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
    case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
        flag = 1;
        break;
    default:
        break;
    }
}


