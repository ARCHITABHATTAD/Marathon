#include "ti_msp_dl_config.h"
#include "stdio.h"
#define UART_TX_SIZE (100)


uint8_t rxData[UART_TX_SIZE];
uint8_t buffer_index = 0;
bool dataReceived;
uint8_t data_length = 0;

int main(void){
    SYSCFG_DL_init();

    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while (1) {
        if(buffer_index >= rxData[1]+1){
            printf("transmitting %d\n ", data_length);
            for(int i=2; i<buffer_index; i++){
                DL_UART_transmitData(UART0, rxData[i]);
                while(DL_UART_isBusy(UART0));
                printf("%c ", rxData[i]);
            }
            printf("\n");
            buffer_index = 0;
            data_length = 0;
        }
        __NOP();
    }
}

void UART_0_INST_IRQHandler(void){
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            while(!DL_UART_isRXFIFOEmpty(UART0)){
                uint8_t one_byte = DL_UART_Main_receiveData(UART0);
                if (buffer_index < UART_TX_SIZE){
                 if (buffer_index == 1){
                    data_length = one_byte;
                 }
                 rxData[buffer_index] = one_byte;
                 buffer_index++;
                }
            }
            break;
        default:
            break;
    }
}
