#include "ti_msp_dl_config.h"
#include "stdio.h"
volatile uint8_t flag = 0;

#define SPI_Psize (4)
uint8_t gTXPacket[SPI_Psize] = { 1, 2, 3, 4 };
volatile uint8_t gRXPacket[SPI_Psize];

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(GPIO_GRP_0_INT_IRQN);
    NVIC_EnableIRQ(SPI_0_INST_INT_IRQN);


    while (1)
    {
        if (0 == flag)
        {
            __WFI();
        }
        DL_SPI_fillTXFIFO8(SPI_0_INST, &gTXPacket[0], SPI_Psize);
        while (DL_SPI_isBusy(SPI_0_INST));

        flag = 0;
    }
}

void SPI_0_INST_IRQHandler(void)
{
    switch (DL_SPI_getPendingInterrupt(SPI_0_INST))
    {
    case DL_SPI_IIDX_RX:
        for (int i = 0; i < SPI_Psize; i++)
        {
            gRXPacket[i] = DL_SPI_receiveDataBlocking8(SPI_0_INST);
            printf("%c \n", gRXPacket[i]);
        }
        break;
    default:
        break;
    }
}

void GROUP1_IRQHandler(void)
{
    switch (DL_GPIO_getPendingInterrupt(GPIO_GRP_0_PORT))
    {
    case DL_GPIO_IIDX_DIO18:
        flag = 1;
        break;
    default:
        break;
    }
}
