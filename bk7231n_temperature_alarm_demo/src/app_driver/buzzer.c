/*
 * @file name: buzzer.c
 * @Descripttion: 
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-26 16:35:33
 * @LastEditors: xjw
 * @LastEditTime: 2021-05-26 18:21:28
 */
/* Includes ------------------------------------------------------------------*/
#include "tuya_timer.h"
#include "buzzer.h"
/* Private define -----------------------------------------------------------*/
#define buzzer_pin  17
/* Private variables ---------------------------------------------------------*/
static tuya_timer_t *timer = NULL;
/* Private function prototypes -----------------------------------------------*/
void tuya_timer0_cb(void *arg);
/* Private functions ---------------------------------------------------------*/
/**
 * @Function: buzzer_pin_init
 * @Description:buzzer_pin_init
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void buzzer_pin_init()
{
        //buzzer pin init
    tuya_pin_init(buzzer_pin, TUYA_PIN_MODE_OUT_PP_LOW);
}
/**
 * @Function: buzzer_set
 * @Description: buzzer_set
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void buzzer_set(IN     BOOL_T bONOFF)
{
        if(bONOFF == TRUE) {
        tuya_pin_write(buzzer_pin, TUYA_PIN_HIGH);
        }else {
        tuya_pin_write(buzzer_pin, TUYA_PIN_LOW);
        }
}
/**
 * @Function: buzzer_start
 * @Description:A passive buzzer drive pulse occurs
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void buzzer_start(void)
{
    timer = (tuya_timer_t *)tuya_driver_find(TUYA_DRV_TIMER, TUYA_TIMER1);
    //The timer uses cycle mode
    TUYA_TIMER_CFG(timer, TUYA_TIMER_MODE_PERIOD, tuya_timer0_cb, NULL);
    tuya_timer_init(timer);
    //Start the timer, 100us is a counting cycle
    tuya_timer_start(timer, 100);
    buzzer_set(1);

}
/**
 * @Function: buzzer_stop
 * @Description: stop buzzer sound
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void buzzer_stop(void)
{
    tuya_timer_stop(timer);
    buzzer_set(0);

}
/**
 * @Function: tuya_timer0_cb
 * @Description: tuya_timer0_cb
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void tuya_timer0_cb(void *arg)
{
    static int level = 1;
    level = ~level;
    buzzer_set(level);
}



