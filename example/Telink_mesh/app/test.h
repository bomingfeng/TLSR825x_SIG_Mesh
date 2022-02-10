
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#include "proj/tl_common.h"

#define debug	0 //0=调试。1=正常



#define BATT_CHECK_ENABLE       			0   //must enable
#if (BATT_CHECK_ENABLE)
//telink device: you must choose one gpio with adc function to output high level(voltage will equal to vbat), then use adc to measure high level voltage
	//use PC5 output high level, then adc measure this high level voltage
	#define GPIO_VBAT_DETECT				GPIO_PB6
	#define PB6_FUNC						AS_GPIO
	#define PB6_INPUT_ENABLE				0
	#define ADC_INPUT_PCHN					B6P    //corresponding  ADC_InputPchTypeDef in adc.h
#endif

enum{
    FLD_OTA_REBOOT_FLAG                 = BIT(0),
    FLD_LOW_BATT_FLG                   	= BIT(1),
    FLD_LOW_BATT_LOOP_FLG             	= BIT(2),	// 0 means check by user_init, 1 means by main loop
};/*DEEP_ANA_REG0*/


/* Dongle 板的2 个按键，做测试button 的IO，默认没有使用。
如果使用的时候，需要改IO，则改完IO 后，还需要同步修改对应的
PULL_WAKEUP_SRC_XXX 和XXX_INPUT_ENABLE。
*/
#define	SW1_GPIO				GPIO_PD6
#define	SW2_GPIO				GPIO_PD5


void test_init(void);
void test_code(void);

//95 16 73 38 c1 a4
/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif