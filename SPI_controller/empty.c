#include "ti_msp_dl_config.h"
#include "stdio.h"
volatile uint8_t flag = 0;
#define SPI_Psize (4)
uint8_t gTXPacket[SPI_Psize] = { 'A', 'B', 'C', 'D' };
volatile uint8_t gRXPackect[SPI_Psize];

int main(void){
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
            gRXPackect[i] = DL_SPI_receiveDataBlocking8(SPI_0_INST);
            printf("%d \n", gRXPackect[i]);
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



//#include "ti_msp_dl_config.h"
//#include "stdio.h"
//
//#define TRUE (1)
//#define FALSE (0)
//#define SPI_BUFFER_SIZE (4)
//#define DATA_SIZE (256)
//
//uint8_t TxData[DATA_SIZE];
//uint16_t ind=0;
//uint16_t remainingBytes =0;
//volatile uint16_t transmit_flag = FALSE;
//uint8_t RxData[DATA_SIZE];
//uint16_t buffer_index =0;
//
//
//void addData(uint8_t* data,uint16_t size){
//    for(uint8_t i=0;i<size;i++){
//        TxData[i] = data[i];
//    }
//    remainingBytes =size;
//}
//void transmitData(){
//    while(remainingBytes>0){
//        uint8_t bytestosend = (remainingBytes > SPI_BUFFER_SIZE) ? SPI_BUFFER_SIZE : remainingBytes;
//        DL_SPI_fillTXFIFO8(SPI_0_INST,&TxData[ind] , bytestosend);
//
//        while(DL_SPI_isBusy(SPI_0_INST));
//        ind += bytestosend;
//        remainingBytes -= bytestosend;
//
//    }
//    ind = 0;
//}
//
//
//int main(void)
//{
//    SYSCFG_DL_init();
//    NVIC_EnableIRQ(SPI_0_INST_INT_IRQN);
//    NVIC_EnableIRQ(GPIO_GRP_0_INT_IRQN);
//    uint8_t msg[] = "Hello this is Archita.Aarushi is my sis !! Love ya. Bye, Signing off!!!";
//        while (1) {
//
//            if(FALSE == transmit_flag){
//                __WFI();
//            }
//
//            addData(msg, sizeof(msg)-1);
//            if(remainingBytes>0){
//                transmitData();
//            }
//            transmit_flag = FALSE;
//
//            for (int i = 0; i < 15; i++){
//                 printf("%c ", RxData[i]);
//            }
//            printf("\n");
//        }
//}
//
//void SPI_0_INST_IRQHandler(void){
//    switch (DL_SPI_getPendingInterrupt(SPI_0_INST)){
//        case DL_SPI_IIDX_RX:
//            while(!DL_SPI_isRXFIFOEmpty(SPI_0_INST)){
//                uint8_t one_byte = DL_SPI_receiveData8(SPI_0_INST);
//                if(buffer_index<SPI_BUFFER_SIZE){
//                    RxData[buffer_index] = one_byte;
//                    buffer_index++;
//                }
//            }
//            break;
//        default:
//            break;
//    }
//}
//
//void GROUP1_IRQHandler(void){
//    switch( DL_GPIO_getPendingInterrupt(GPIO_GRP_0_PORT)){
//    case DL_GPIO_IIDX_DIO18:
//        transmit_flag = TRUE;
//        break;
//    default:
//        break;
//    }
//}
