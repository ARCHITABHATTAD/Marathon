#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    uint32_t DAC_out = 4095;

    DL_DAC12_output12(DAC0, DAC_out);
    DL_DAC12_enable(DAC0);
    while (1) {
        __WFI();
    }
}
