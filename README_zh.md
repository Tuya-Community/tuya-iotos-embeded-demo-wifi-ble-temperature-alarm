# Tuya IoTOS Embeded Demo WiFi & BLE temperature alarm

[English](./README.md) | [中文](./README_zh.md)

## 简介 

本 Demo 基于涂鸦智能云平台、涂鸦智能APP、IoTOS Embeded WiFi &Ble SDK，使用涂鸦WiFi/WiFi+BLE系列模组和B3950_10K热敏电阻以及无源蜂鸣器快速组建一个温度报警器demo，可以自行设置温度阈值作为报警界限值，当温度高于界限值时将声音报警。

## 快速上手

### 编译与烧录
+ 下载[Tuya IoTOS Embeded WiFi & BLE sdk](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231n) 

+ 下载Demo至SDK目录的apps目录下 

  ```bash
  $ cd apps
$ git clone https://registry.code.tuya-inc.top/hardware_developer/tuya-iotos-embeded-demo-wifi-ble-temperature-alarm.git
  ```

+ 在SDK根目录下执行以下命令开始编译：

  ```bash
  sh build_app.sh apps/bk7231n_temperature_alarm_demo bk7231n_temperature_alarm_demo 1.0.0 
  ```

+ 固件烧录授权相关信息请参考：[Wi-Fi + BLE 系列模组烧录授权](https://developer.tuya.com/cn/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd) 



### 文件介绍
```
├── src	
|    ├── app_driver
|    |    └── b3950_10k.c            //温度传感器驱动相关
|    |    └── buzzer.c            //无源蜂鸣器驱动相关
|    ├── tuya_device.c             //应用层入口文件
|    └── app_temperature_alarm.c            //主要应用层
|
├── include				//头文件目录
|    ├── app_driver
|    |    └──b3950_10k.h
|    |    └──buzzer.h
|    ├── tuya_device.h
|    └── app_temperature_alarm.h
|
└── output              //编译产物
```

<br>

### 应用入口
入口文件：tuya_device.c

重要函数：device_init()

+ 调用 tuya_iot_wf_soc_dev_init_param() 接口进行SDK初始化，配置了工作模式、配网模式，同时注册了各种回调函数并存入了固件key和PID。
+ 调用 tuya_iot_reg_get_wf_nw_stat_cb() 接口注册设备网络状态回调函数。
+ 调用应用层初始化函数app_temper_alarm_init()。

<br>

### dp点相关

+ 下发dp点数据流：dev_obj_dp_cb() -> deal_dp_proc()
+ 上报dp点接口: dev_report_dp_json_async()

|函数名 | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt)|
|	---|---|
|    devid | 设备id（若为网关、MCU、SOC类设备则devid = NULL;若为子设备，则devid = sub-device_id)|
|    dp_data | dp结构体数组名|
|    cnt |dp结构体数组的元素个数|
|    Return    |  OPRT_OK: 成功  Other: 失败 |
<br>

### I/O 列表

|temperature alarm||
| --- | --- |
|`TUYA_ADC2`|ADC|
|buzzer_pin| P17  |



<br>



## 相关文档

涂鸦Demo中心：https://developer.tuya.com/demo


<br>


## 技术支持

您可以通过以下方法获得涂鸦的支持:

- 开发者中心：https://developer.tuya.com
- 帮助中心: https://support.tuya.com/help
- 技术支持工单中心: [https://service.console.tuya.com](https://service.console.tuya.com/) 


<br>


