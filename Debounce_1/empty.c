#include "ti_msp_dl_config.h"

volatile uint8_t current_btn_state = 0;
volatile uint8_t previous_btn_state = 0;
volatile uint8_t lstable_btn_state = 0;
volatile uint8_t btn_pressed = 0;

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_INST);
    while (1) {
        __WFI();

        if(current_btn_state==previous_btn_state){
            if(current_btn_state!=lstable_btn_state){
                if(current_btn_state){
                    btn_pressed = 1;
                }
            }
            lstable_btn_state = current_btn_state;
        }
        previous_btn_state = current_btn_state;

        if(btn_pressed){
            DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN);
            btn_pressed=0;
        }
    }
}

void TIMER_INST_IRQHandler(void){
    if(DL_GPIO_readPins(GPIO_BTN_PORT, GPIO_BTN_PIN)){
        current_btn_state =1;
    }
    else{
        current_btn_state =0;
    }
}
