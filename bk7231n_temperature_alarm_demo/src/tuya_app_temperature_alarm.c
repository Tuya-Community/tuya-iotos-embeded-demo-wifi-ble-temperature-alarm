/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_temperature_alarm.c
 * @Description: temperature alarm demo main application file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-5-26 15:22:03
 * @LastEditTime: 2021-05-26 18:35:04
 */
/* Includes ------------------------------------------------------------------*/
#include "tuya_iot_wifi_api.h"
#include "tuya_hal_thread.h"
#include "uni_thread.h"
#include "uni_log.h"
/* Private includes ----------------------------------------------------------*/
#include "tuya_b3950_100k.h"
#include "tuya_app_temperature_alarm.h"
#include "tuya_buzzer.h"
/* Private variables ---------------------------------------------------------*/
DP_VALUE_T set_alarm_temper_s = {
    .dp_id = DP_ALARM_TEMPER_SET,
    .value = 0,
};
DP_VALUE_T status_s = {
    .dp_id = DP_STATUS,
    .value = 0,
};
STATIC MUTEX_HANDLE mutex = NULL;
/* Private function prototypes -----------------------------------------------*/
STATIC VOID app_temper_alarm(PVOID_T pArg);
/* Private functions ---------------------------------------------------------*/
/*b3590 test init*/
/**
 * @Function: app_temper_alarm_init
 * @Description: app_temper_alarm_init
 * @Input: APP_MODE：Application mode
 * @Output: none
 * @Return: op_ret   execution result
 * @Others: 
 */
OPERATE_RET app_temper_alarm_init(IN APP_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;

    if(APP_NORMAL == mode) {
        b3950_init();
        buzzer_pin_init();
        set_alarm_temperature(30);
            // create mutex
        if(NULL == mutex) {
            op_ret = tuya_hal_mutex_create_init(&mutex);
            if(OPRT_OK != op_ret) {
                PR_ERR("tuya_hal_mutex_create_init err:%d",op_ret);
                return op_ret;
            }
        }
        
        op_ret = tuya_hal_thread_create(NULL, "app_temper_alarmt", 512*4, TRD_PRIO_5, app_temper_alarm, NULL);
        if (op_ret != OPRT_OK) {
            PR_ERR("Create app_temper_alarm error!: %d", op_ret); 
            return;
        }
    }else {
        //not factory test mode
    }

    return op_ret;
}
/**
 * @Function: get_alarm_temperature value
 * @Description: get_alarm_temperature value
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
int get_alarm_temperature_value()
{   

    return set_alarm_temper_s.value;

}
/**
 * @Function: get_dp_status_value 
 * @Description: get_dp_status_value 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
int get_dp_status_value()
{   

    return status_s.value;

}
/**
 * @Function: set_alarm_temperature
 * @Description: set_alarm_temperature
 * @Input: int value
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID set_alarm_temperature(int value)
{   
    if(29 < value <201) {
        tuya_hal_mutex_lock(mutex);
        set_alarm_temper_s.value = value;
        tuya_hal_mutex_unlock(mutex);
    }
}
/**
 * @Function: set_dp_status_value
 * @Description: set_dp_status_value
 * @Input: bool status
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID set_dp_status_value(bool status)
{   
        tuya_hal_mutex_lock(mutex);
        status_s.value = status;
        tuya_hal_mutex_unlock(mutex);
}
/**
 * @Function: app_temper_alarm
 * @Description: app_temper_alarm thread function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
STATIC VOID app_temper_alarm(PVOID_T pArg)
{   
    static int temp_temperature = 0;
    while(1) {

        temp_temperature = cur_temper_get();
        PR_DEBUG("temper_value:%d",temp_temperature);
        if(temp_temperature > get_alarm_temperature_value()) {
            if(get_dp_status_value() == FALSE) {
                set_dp_status_value(TRUE);
                buzzer_start();
                report_one_dp_status(DP_STATUS);
            }
        }else {
            if(get_dp_status_value() == TRUE) {
                set_dp_status_value(FALSE);
                buzzer_stop();
                report_one_dp_status(DP_STATUS);
            }

        }
        /*delay 2s */
        tuya_hal_system_sleep(2000);
    }
}

/**
 * @Function: report_one_dp_status
 * @Description:update the dp data
 * @Input: int dp_id
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID_T report_one_dp_status(int dp_id)
{
    
    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E wifi_state = 0xFF;
    op_ret = get_wf_gw_nw_status(&wifi_state);
    if (OPRT_OK != op_ret) {
        PR_ERR("get wifi state err");
        return;
    }
    if (wifi_state <= STAT_AP_STA_DISC || wifi_state == STAT_STA_DISC) {
        return;
    }
    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }
    memset(dp_arr, 0, SIZEOF(TY_OBJ_DP_S));

    switch (dp_id){
    case DP_ALARM_TEMPER_SET: {
        dp_arr[0].dpid = set_alarm_temper_s.dp_id;
        dp_arr[0].type = PROP_VALUE;
        dp_arr[0].time_stamp = 0;
        dp_arr[0].value.dp_bool = set_alarm_temper_s.value;

        }
        break;

    case DP_STATUS: {
        dp_arr[0].dpid = status_s.dp_id;
        dp_arr[0].type = PROP_ENUM;
        dp_arr[0].time_stamp = 0;
        dp_arr[0].value.dp_value = status_s.value;
        }
        break;

    default:
    
        break;
    }

    op_ret = dev_report_dp_json_async(NULL , dp_arr, 1);
    Free(dp_arr);
    dp_arr = NULL;
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }
}
/**
 * @Function: deal_dp_proc
 * @Description: dp data deal function
 * @Input: TY_OBJ_DP_S 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);
    
    switch (dpid) {
    
    case DP_ALARM_TEMPER_SET: {
        set_alarm_temperature(root->value.dp_value);
        
        }
        break;

    default:
        break;
    }

}