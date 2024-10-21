#include "ti_msp_dl_config.h"


#define MIN 10
#define MAX 50
#define BASE 10

volatile uint8_t count = 10;
volatile uint8_t delay_counter = 10;
volatile uint8_t current_btn_state_1 =0;
volatile uint8_t previous_btn_state_1 =0;
volatile uint8_t lstable_btn_state_1 =1;


volatile uint8_t current_btn_state_2 =0;
volatile uint8_t previous_btn_state_2 =0;
volatile uint8_t lstable_btn_state_2 =1;

int btn_1_pressed(){
    if(current_btn_state_1==previous_btn_state_1){
        if(current_btn_state_1 != lstable_btn_state_1){
            if(current_btn_state_1){
                lstable_btn_state_1 =1;
                return 1;
            }
            else{
                lstable_btn_state_1 =0;
            }
        }
    }
    return 0;
}

int btn_2_pressed(){
    if(current_btn_state_2==previous_btn_state_2){
        if(current_btn_state_2 != lstable_btn_state_2){
            if(current_btn_state_2){
                lstable_btn_state_2 =1;
                return 1;
            }
            else{
                lstable_btn_state_2 =0;
            }
        }
    }
    return 0;
}

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);
    while (1) {
        if(delay_counter==0){
            DL_GPIO_togglePins(GPIO_GRP_LED_PORT, GPIO_GRP_LED_PIN);
            delay_counter = count;
        }

        if(btn_1_pressed()){
            if(delay_counter<= MAX){
                count += BASE;
            }
        }
        if(btn_2_pressed()){
            if(delay_counter> MIN){
                count -= BASE;
             }
        }

    }
}

void TIMER_0_INST_IRQHandler(void){
    previous_btn_state_1 = current_btn_state_1;
    previous_btn_state_2 = current_btn_state_2;

    DL_GPIO_readPins(GPIO_GRP_BTN_1_PORT,GPIO_GRP_BTN_1_PIN) ? (current_btn_state_1 =1): (current_btn_state_1=0);
    DL_GPIO_readPins(GPIO_GRP_BTN_2_PORT,GPIO_GRP_BTN_2_PIN) ? (current_btn_state_2 =1): (current_btn_state_2=0);


    if(delay_counter>0){
        delay_counter--;
    }
}

