/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: b3950_100k.c
 * @Description: b3950 sensor init process 
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-5-26 15:22:03
 * @LastEditTime: 2021-05-26 18:35:04
 */
/* Private includes ----------------------------------------------------------*/
#include "tuya_b3950_100k.h"

/* Private variables ---------------------------------------------------------*/
tuya_adc_t *temper_adc;
UINT16_T adc_buf = 0;
float volt = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 * @Function: b3950_init
 * @Description: b3950-temperature-sensor init
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void b3950_init(void)
{
    /*create adc device,get handle*/
    temper_adc = (tuya_adc_t *)tuya_driver_find(TUYA_DRV_ADC, TUYA_ADC2);
    /*adc_dev cfg*/
    TUYA_ADC_CFG(temper_adc, TUYA_ADC2, 0);
    /*adc_dev init*/
    tuya_adc_init(temper_adc);
}
/**
 * @Function: cur_temper_get
 * @Description: current temperature get
 * @Input: none
 * @Output: none
 * @Return: temperature value
 * @Others: 
 */
int  cur_temper_get()
{
    int Rt = 0;
    float Rp = 100000;
    float T2 = 273.15 + 25;
    float Bx = 3950;
    float Ka = 273.15;
    int temp = 0;
    /*Collect AD data and store it in adc_buffer*/
    tuya_adc_convert(temper_adc, &adc_buf, 1);
    /*req_val(0-4096) - V(0-2.4)*/
    volt = (float)adc_buf *2.4/ 4096;
    //volt = adc_buf;
    Rt = (3.3 - volt)*20000/volt;
    PR_DEBUG("Rt:%d", Rt);
    temp = (int)(1/(1/T2+log(Rt/Rp)/Bx)-Ka+0.5);
    PR_DEBUG("volt:%f", volt);
    return temp;


}