/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
#include "input.h"
#include "bsp_core_board_control_io.h"
#include "string.h"
#include "brake_control.h"
#include "fault_check.h"
#include "self_check.h"
#include "comm.h"
#include "EDV.h"
#include "PID.h"
#include "init.h"
#include "output.h"

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
//  MX_DMA_Init();
  MX_CAN_Init();
  MX_TIM1_Init();
//  MX_USART1_UART_Init();
//  MX_USART3_UART_Init();
//  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
  BCU_Init();
  /* USER CODE END 2 */
//  Flash_EnableReadProtection();		//����flash����������ֹflash�еĿ�ִ�д��뱻�������
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if(cycle_flag > 0)
	{	
		cycle_flag = 0;
		cpu_life_signal++;
		WTD();
		IO_RecvData();
		Get_Input();
		BCU_Fault_Check();
		
		if(bcu_mode.master)	//����
		{
			if(~M_ENABLE_ALL)	//�ƶ���δ����
			{
				if(bcu_pos.d_mul)	//��բ����λ
				{
					D_Mul_Logic();
				}
				
				else if(bcu_pos.d_emc)	//��բ����λ
				{
					D_Emc_Logic();
				}
			}
			else
			{
				if(Get_Check_State(&bcu_pos) || check_busy)
				{
					BCU_Self_Check();
				}
				else
				{
					Logic_All_Pre();
					
					if(bcu_pos.d_oc)		//��բ����λ
					{
						D_Oc_Logic();
					}
					
					else if(bcu_pos.d_run)	//��բ��תλ
					{
						D_Run_Logic();
					}
					
					else if(bcu_pos.d_brk)	//��բ�ƶ�λ
					{
						D_Brk_Logic();
					}
					
					else if(bcu_pos.d_res)	//��բ����λ
					{
						D_Res_Logic();
					}
					
					else if(bcu_pos.d_mul)	//��բ����λ
					{
						D_Mul_Logic();
					}
					
					else if(bcu_pos.d_emc)	//��բ����λ
					{
						D_Emc_Logic();
					}
					
					if(bcu_pos.s_zero)		//˾��������λ�߼�
					{
						S_Zero_Logic();
					}
					
					else if(bcu_pos.s_brake_area)	//˾�������ƶ����߼�
					{
						S_Brake_Area_Logic();
					}
					
					else if(bcu_pos.s_fast_brake)	//˾�����������ƶ��߼�
					{
						S_Fast_Brake_Logic();
					}
				}
				PO2_EBV = EDV(&bcu_mode,&bcu_switch,&bcu_press);
//				PO2 = XZ_Logic();
			}
		}
		else if(bcu_mode.slave)	//�ӻ�
		{
			BCU_Slave_Logic();
		}
		PID_Control();
		Select_Output_Board_And_Write(Output_Board_1, doutdata[0]);
		Select_Output_Board_And_Write(Output_Board_1, doutdata[1]);
		Updata_Brake_Pos(&bcu_pos,&bcu_last_pos);
		
		CAN1_SendData();
		CAN2_SendData();
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
