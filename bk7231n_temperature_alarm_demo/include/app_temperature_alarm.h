/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_temperature_alarm.h
 * @Description: temperature alarm demo main application file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-26 16:50:03
 * @LastEditTime: 2021-05-26 18:50:14
 */

#ifndef __APP_TEMPERATURE_ALARM_H__
#define __APP_TEMPERATURE_ALARM_H__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/***********************************************************
*************************variable define********************
***********************************************************/
#define DP_ALARM_TEMPER_SET 101
#define DP_STATUS   102
typedef enum{
    APP_NORMAL,       //normal mode
    APP_PRODTEST      //prodact test mode
}APP_MODE;


typedef struct {
    UINT8_T dp_id;
    
    int value;
}DP_VALUE_T;
/********************************************************************************
 * FUNCTION:       app_temper_alarm_init
 * DESCRIPTION:    application initialization
 * INPUT:          mode:application mode
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-05-26
 *******************************************************************************/
OPERATE_RET app_temper_alarm_init(IN APP_MODE mode);

/********************************************************************************
 * FUNCTION:       deal_dp_proc
 * DESCRIPTION:    deal the data sented by app
 * INPUT:          root:app issued data structure
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-05-26
 *******************************************************************************/
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root);

/*********************************************************************************
 * FUNCTION:       report_one_dp_status
 * DESCRIPTION:    report all dp date
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         dp_cnt needs to be modified when adding or deleting the dp function
 * HISTORY:        2021-05-26
 *******************************************************************************/
VOID_T report_one_dp_status(int dp_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __LIHGT_INIT_H__ */