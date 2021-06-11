/*
 * @file name: 
 * @Descripttion: 
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-26 16:44:58
 * @LastEditors: xjw
 * @LastEditTime: 2021-05-26 18:49:02
 */
#ifndef __TUYA_BUZZER_H__
#define __TUYA_BUZZER_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "tuya_pin.h"
#include "tuya_hal_system.h"

/*============================ MACROFIED FUNCTIONS ===========================*/
void buzzer_start(void);
void buzzer_pin_init();
void buzzer_stop(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif