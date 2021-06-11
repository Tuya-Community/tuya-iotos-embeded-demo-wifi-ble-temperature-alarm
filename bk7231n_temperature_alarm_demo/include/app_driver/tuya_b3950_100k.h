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
#ifndef __TUYA_B3950_100K_H__
#define __TUYA_B3950_100K_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "tuya_adc.h"

void b3950_init(void);
int  cur_temper_get();
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif