#include "proj/tl_common.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll_whitelist.h"
#include "proj_lib/ble/trace.h"
#include "proj_lib/ble/ble_common.h"
#include "proj/mcu/pwm.h"
#include "proj_lib/ble/service/ble_ll_ota.h"
#include "proj/drivers/adc.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ble_smp.h"
#include "proj_lib/mesh_crypto/mesh_crypto.h"
#include "proj_lib/mesh_crypto/mesh_md5.h"
#include "proj_lib/mesh_crypto/sha256_telink.h"
#include "proj_lib/sig_mesh/app_mesh.h"
#include "mesh/app_provison.h"
#include "mesh/app_beacon.h"
#include "mesh/app_proxy.h"
#include "mesh/app_health.h"
#include "mesh/vendor_model.h"
#include "proj/drivers/keyboard.h"
#include "app.h"
#include "stack/ble/gap/gap.h"
#include "proj_lib/ble/l2cap.h"
#include "mesh/blt_soft_timer.h"
#include "proj/drivers/rf_pa.h"
#include "proj/common/types.h"
#include "mesh/battery_check.h"

#include "test.h"


#if MI_API_ENABLE
#include "mesh/mi_api/telink_sdk_mible_api.h"
#include "mesh/mi_api/certi/mijia_profiles/mi_service_server.h"
#endif 
#if (HCI_ACCESS==HCI_USE_UART)
#include "proj/drivers/uart.h"
#endif


/* */
void  led_init(void)
{
	/* ��Ҫ�����ó���ͨIO���Ǹ��ø߼�����(uart��spi��iic��) */
	gpio_set_func(GPIO_PC2, AS_GPIO);
	gpio_set_func(GPIO_PC3, AS_GPIO);
	gpio_set_func(GPIO_PC4, AS_GPIO);
	gpio_set_func(GPIO_PB4, AS_GPIO);
	gpio_set_func(GPIO_PB5, AS_GPIO);

	/* ���ʹ�� */
	gpio_set_output_en(GPIO_PC2, 1);
	gpio_set_output_en(GPIO_PC3, 1);
	gpio_set_output_en(GPIO_PC4, 1);
	gpio_set_output_en(GPIO_PB4, 1);
	gpio_set_output_en(GPIO_PB5, 1);

	/* ����ʹ�� */
	gpio_set_input_en(GPIO_PC2, 0); 
	gpio_set_input_en(GPIO_PC3, 0); 
	gpio_set_input_en(GPIO_PC4, 0); 
	gpio_set_input_en(GPIO_PB4, 0); 
	gpio_set_input_en(GPIO_PB5, 0); 

	gpio_set_func(GPIO_PD2, AS_GPIO);
	/* ���������� */
	gpio_setup_up_down_resistor(GPIO_PD2, PM_PIN_PULLUP_10K);
	gpio_set_output_en(GPIO_PD2, 0);
	gpio_set_input_en(GPIO_PD2, 1); 	
}

void my_key_proocess(void)
{
	int c = 20;
	while (c--)
	{	
		/* ��ȡ�ܽŵ�ƽ */
		if(gpio_read(GPIO_PD2) == 0)
		{
			while (gpio_read(GPIO_PD2) == 0){sleep_ms(1);};

			sleep_ms(20);
			while (1)
			{
				if(gpio_read(GPIO_PD2) == 0) 
				{
					while (gpio_read(GPIO_PD2) == 0){sleep_ms(1);};
					return;
				}
				sleep_ms(1);
			}
		}
		sleep_ms(10);
	}
}

void led_loop (void)
{
	gpio_write(GPIO_PC2, 1); 
	gpio_write(GPIO_PC3, 0); 
	gpio_write(GPIO_PC4, 0); 
	gpio_write(GPIO_PB4, 0); 
	gpio_write(GPIO_PB5, 0);  
	my_key_proocess();

	gpio_write(GPIO_PC2, 0); 
	gpio_write(GPIO_PC3, 1); 
	gpio_write(GPIO_PC4, 0); 
	gpio_write(GPIO_PB4, 0); 
	gpio_write(GPIO_PB5, 0); 
	my_key_proocess();

	gpio_write(GPIO_PC2, 0); 
	gpio_write(GPIO_PC3, 0); 
	gpio_write(GPIO_PC4, 1); 
	gpio_write(GPIO_PB4, 0); 
	gpio_write(GPIO_PB5, 0); 
	my_key_proocess();

	gpio_write(GPIO_PC2, 0); 
	gpio_write(GPIO_PC3, 0); 
	gpio_write(GPIO_PC4, 0); 
	gpio_write(GPIO_PB4, 1); 
	gpio_write(GPIO_PB5, 0); 
	my_key_proocess();

	gpio_write(GPIO_PC2, 0); 
	gpio_write(GPIO_PC3, 0); 
	gpio_write(GPIO_PC4, 0); 
	gpio_write(GPIO_PB4, 0); 
	gpio_write(GPIO_PB5, 5); 
	my_key_proocess();
}


extern u16     batt_vol_mv;
/*  main�п����ж�ǰ�����ڲ��Դ����ʼ��*/ 
void test_init(void)
{
	//led_init();
	#if (BATT_CHECK_ENABLE)
    //app_battery_power_check_and_sleep_handle(0); /* 0=��ʼ�� */ //battery check must do before OTA relative operation
    //LOG_USER_MSG_INFO(0,0,"battery user init normal, current:%d, ana reg0:0x%x", batt_vol_mv, analog_read(DEEP_ANA_REG0));
	#endif
}


u8 data_test[4]={1,2,3,4};
u8 data_val = 0xff;
u32 test_time;

/* main�е�while(1)�У����ڲ��Ի���ѭ��*/
void test_code(void)
{
	/* */
	//led_loop();

	/* */
	//LOG_USER_MSG_INFO(0, 0,"[mesh] LOG_USER_MSG_INFO", 0);/* LOG_USER_MSG_INFO */

	//LOG_USER_MSG_INFO(data_test,sizeof(data_test),"LOG_USER_MSG_INFO %d ",(data_val--)); /* LOG_USER_MSG_INFO %d data_test */

	//LOG_MSG_INFO(TL_LOG_MESH,0, 0,"[mesh] LOG_MSG_INFO", 0);/* LOG_MSG_INFO */

	//LOG_MSG_INFO(TL_LOG_MESH,data_test,sizeof(data_test),"LOG_MSG_INFO %d ",(data_val--)); /* LOG_MSG_INFO %d data_test */

	/* */
	//if(clock_time_exceed(test_time, 10000*1000)) /* 10���ӡһ�Σ���λΪUS��һ�����ڶ����Ҫ�����ر���̵�Ӧ�� */
	//{
    //    test_time = clock_time();
    //   LOG_USER_MSG_INFO(0, 0,"10S print test_time:%d,clock_time:%d", test_time,clock_time());
    //}

	/* */
	#if (BATT_CHECK_ENABLE)
    //app_battery_power_check_and_sleep_handle(1); /* 1=��ȡ��ѹ */ //battery check must do before OTA relative operation
    //LOG_USER_MSG_INFO(0,0,"battery loop normal, current:%d, ana reg0:0x%x", batt_vol_mv, analog_read(DEEP_ANA_REG0));
	#endif
}

/*
System start ............

rcv provision invite 00 05
send capa cmd 01 01 00 01 00 01 00 00 00 00 00 00
gatt the start cmd is invalid
gatt rcv err opcode in the LINK_UNPROVISION_STATE state

System start ............
mesh tx NoAck,op:0x4e82,src:0x0004,dst:0xffff,par:ff ff
tx_access:key array index not existed,nk:0,ak:2
not found app key
mesh_tx_cmd_layer_upper:not found device or app key
*/

/*
����MCU����˯�ߺͻ��ѵ�API
int cpu_sleep_wakeup(SleepMode_TypeDef sleep_mode,SleepWakeupSrc_TypeDef wakeup_src,unsigned int wakeup_tick);
* @brief �˹����������û��� 32k ����� MCU ����ģʽ������ ����ģʽ�����˯��ģʽ������ SRAM ����ģʽ�͹ػ�ģʽ�����˯�ߡ�
  * @param[in] sleep_mode - ˯��ģʽ����ѡ��
  * @param[in] wakeup_src - ����Դѡ��
  * @param[in] wakeup_tick - ��˯��ʱ�䣬����ζ�� MCU ����˯������ 5 ���ӡ����û������PM_WAKEUP_TIMER���ѣ��ò���������
  * @return ָʾcpu �Ƿ��ѳɹ���
*/

/* ȫ�������ļ�˵��
mesh_config.h
mesh_node.h
app_mesh.h 
*/