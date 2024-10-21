#include "ti_msp_dl_config.h"


#define LED1_ON (50)
#define LED1_OFF (80)
#define LED2_ON (70)
#define LED2_OFF (40)

volatile uint8_t current_btn_state_1 = 0;
volatile uint8_t previous_btn_state_1 = 0;
volatile uint8_t lstable_btn_state_1 = 1;

volatile uint8_t current_btn_state_2 = 0;
volatile uint8_t previous_btn_state_2 = 0;
volatile uint8_t lstable_btn_state_2 = 1;

volatile uint8_t timer_counter =0;


volatile uint8_t on_1 =0;
volatile uint8_t off_1 =0;
volatile uint8_t on_2 =0;
volatile uint8_t off_2 =0;

int btn_1_status(){
    if(current_btn_state_1==previous_btn_state_1){
        if(current_btn_state_1!=lstable_btn_state_1){
            if(current_btn_state_1){
                lstable_btn_state_1 = 1;
                return 1;
            }
            else{
                lstable_btn_state_1 = 0;
            }
        }
    }
    return 0;
}

int btn_2_status(){
    if(current_btn_state_2==previous_btn_state_2){
            if(current_btn_state_2!=lstable_btn_state_2){
                if(current_btn_state_2){
                    lstable_btn_state_2 = 1;
                    return 1;
                }
                else{
                    lstable_btn_state_2 = 0;
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
    DL_GPIO_setPins(GPIO_GRP_0_LED_2_PORT,GPIO_GRP_0_LED_2_PIN);
    DL_GPIO_clearPins(GPIO_GRP_0_LED_1_PORT,GPIO_GRP_0_LED_1_PIN);
    while (1) {
        if(btn_1_status()){
            on_1 =0 ;
            off_1 = 0;
            DL_GPIO_clearPins(GPIO_GRP_0_LED_1_PORT,GPIO_GRP_0_LED_1_PIN);
            off_1 = timer_counter + (LED1_OFF);
        }
        if(btn_2_status()){
            on_2 =0 ;
            off_2 = 0;
            DL_GPIO_setPins(GPIO_GRP_0_LED_2_PORT,GPIO_GRP_0_LED_2_PIN);
            off_2 = timer_counter + (LED2_OFF);
        }
        if(timer_counter == off_1){
            DL_GPIO_setPins(GPIO_GRP_0_LED_1_PORT,GPIO_GRP_0_LED_1_PIN);
            off_1 = 0;
            on_1 = timer_counter+(LED1_ON);
        }
        if(timer_counter == on_1){
            DL_GPIO_clearPins(GPIO_GRP_0_LED_1_PORT,GPIO_GRP_0_LED_1_PIN);
            on_1 = 0;
        }
        if(timer_counter == off_2){
            DL_GPIO_clearPins(GPIO_GRP_0_LED_2_PORT,GPIO_GRP_0_LED_2_PIN);
            off_2 = 0;
            on_2 = timer_counter+(LED2_ON);
        }
        if(timer_counter == on_2){
            DL_GPIO_setPins(GPIO_GRP_0_LED_2_PORT,GPIO_GRP_0_LED_2_PIN);
            on_2 = 0;
        }
    }
}

void TIMER_0_INST_IRQHandler(void){
    timer_counter++;
    previous_btn_state_1 = current_btn_state_1;
    previous_btn_state_2 = current_btn_state_2;

    (DL_GPIO_readPins(GPIO_GRP_0_BTN_1_PORT,GPIO_GRP_0_BTN_1_PIN)) ? (current_btn_state_1=1) : (current_btn_state_1 =0);
    (DL_GPIO_readPins(GPIO_GRP_0_BTN_2_PORT,GPIO_GRP_0_BTN_2_PIN)) ? (current_btn_state_2=1) : (current_btn_state_2 =0);
}
