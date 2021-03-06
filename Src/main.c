/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NRF24.h"
#include <string.h>
#include "usbd_cdc_if.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	char str1[150]={0}; //for test channel
//	uint16_t buf1[20] = {0}; //for transmit to air
//	char str_tx[21] = {0}; // to transmit to USB
//	char str_rx[21]; // to recieve from USB
	uint8_t recBufLen = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
uint8_t NRF24L01_Send(uint8_t *pBuf);
void NRF24L01_Receive(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//////uint8_t dt_reg=0; for testing a channel
	//uint8_t retr_cnt; // for counter
	//uint16_t i = 1, retr_cnt_full; // the same
//	uint8_t i = 0; // for FOR
	uint8_t dt;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(200);
	NRF24_ini();
//							sprintf(str_tx,"USB Transmit\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(recBufLen > 0)
		{
//HAL_Delay(250);
				dt = NRF24L01_Send((uint8_t*)UserRxBufferFS);
				CDC_Transmit_FS((uint8_t*)UserRxBufferFS, recBufLen);
				recBufLen = 0;
		}
//		int i = 1;
//		memcpy(str_tx,(char*)&UserRxBufferFS,64);
//		CDC_Transmit_FS((unsigned char*)str_tx, strlen(str_tx));
//		for(i = 0; i <= 63; i++)
//		{
//		UserRxBufferFS[i] = 0;
//		}
				//for (i = 0; i < 63; i++) {free((char*)&UserRxBufferFS[i]);}

//                HAL_Delay(500);
//////		HAL_Delay(1000);
//////		char string[] = "12345678987654321sdfgjdynujydfghnyrfgdf";
//////		memcpy(buf1,(uint8_t*)&string,30);
//		if(retr_cnt_full>999) retr_cnt_full=999;
//		memcpy(buf1+2,(uint8_t*)&retr_cnt_full,2);
//////		dt = NRF24L01_Send((uint8_t*)buf1);
//////		CDC_Transmit_FS((uint8_t*)string,strlen((const char*)string));
//    LED_TGL;

////////		retr_cnt = dt & 0xF;
////////		i++;
////////		retr_cnt_full += retr_cnt;
////////		if(i>=999) i=1;
////  dt_reg = NRF24_ReadReg(CONFIG);
////  sprintf(str1,"CONFIG: 0x%02Xrn",dt_reg);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  dt_reg = NRF24_ReadReg(EN_AA);
////  sprintf(str1,"EN_AA: 0x%02Xrn",dt_reg);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  dt_reg = NRF24_ReadReg(EN_RXADDR);
////  sprintf(str1,"EN_RXADDR: 0x%02Xrn",dt_reg);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  dt_reg = NRF24_ReadReg(STATUS);
////  sprintf(str1,"STATUS: 0x%02Xrn",dt_reg);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  dt_reg = NRF24_ReadReg(RF_SETUP);
////  sprintf(str1,"RF_SETUP: 0x%02Xrn",dt_reg);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  NRF24_Read_Buf(TX_ADDR,buf1,3);
////  sprintf(str1,"TX_ADDR: 0x%02X, 0x%02X, 0x%02Xrn",buf1[0],buf1[1],buf1[2]);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
////  NRF24_Read_Buf(RX_ADDR_P0,buf1,3);
////  sprintf(str1,"RX_ADDR: 0x%02X, 0x%02X, 0x%02Xrn",buf1[0],buf1[1],buf1[2]);
////CDC_Transmit_FS((uint8_t*)str1,strlen(str1));
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		NRF24L01_Receive();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

   if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
    Error_Handler();  
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {
    
  }
  LL_PWR_EnableBkUpAccess();
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
  LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_HSE_DIV128);
  LL_RCC_EnableRTC();
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
    
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  
  }
  LL_SetSystemCoreClock(72000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();  
  };
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
