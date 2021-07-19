/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint32_t       TxMailbox;
unsigned char  TxData[8] = {0};
unsigned char  RxData[8] = {0};
unsigned char  rx1[8] = {0};
unsigned char  rx2[8] = {0};
unsigned char  rx3[8] = {0};
unsigned char  rx4[8] = {0};
unsigned char  rx5[8] = {0};
unsigned char  rx6[8] = {0};

unsigned char test1=0;

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */
  CAN_FilterTypeDef  sFilterConfig;

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 120;
  hcan.Init.Mode = CAN_MODE_LOOPBACK; //CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = ENABLE;
  hcan.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* Configure the CAN Filter */
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;
 
  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }

  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
	
  /* Activate CAN TX notification */
//  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
//  {
//    /* Notification Error */
//    Error_Handler();
//  }
  
  /* Configure Transmission process */
  TxHeader.StdId = 0x00;
  TxHeader.ExtId = 0x01;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_EXT;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;	

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void CAN_SendData(void)
{
	
	/****************************源：主BCU 宿：主LCDM（ID：16  8）****************************/
	TxHeader.ExtId = 0x2010000;
	TxData[0]=0x61;
	TxData[1]=0x62;
	TxData[2]=0x63;
	TxData[3]=0x64;
	TxData[4]=0x65;
	TxData[5]=0x66;
	TxData[6]=0x67;
	TxData[7]=0x68;
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}	


	/****************************源：主BCU 宿：主LCDM（ID：17  8）****************************/
	TxHeader.ExtId = 0x2210000;
	TxData[0]=0x71;
	TxData[1]=0x72;
	TxData[2]=0x73;
	TxData[3]=0x74;
	TxData[4]=0x75;
	TxData[5]=0x76;
	TxData[6]=0x77;
	TxData[7]=0x78;
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}	

	/****************************源：主BCU 宿：主LCDM（ID：18  8）****************************/
	TxHeader.ExtId = 0x2410000;
	TxData[0]=0x81;
	TxData[1]=0x82;
	TxData[2]=0x83;
	TxData[3]=0x84;
	TxData[4]=0x85;
	TxData[5]=0x86;
	TxData[6]=0x87;
	TxData[7]=0x88;
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}	
	
//	/****************************源：主BCU 宿：主LCDM（ID：19  8）****************************/
//	TxHeader.ExtId = 0x261;
//	TxData[0]=0x91;
//	TxData[1]=0x92;
//	TxData[2]=0x93;
//	TxData[3]=0x94;
//	TxData[4]=0x95;
//	TxData[5]=0x96;
//	TxData[6]=0x97;
//	TxData[7]=0x98;
//	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
//	{
//		/* Transmission request Error */
//		Error_Handler();
//	}
//	
//	/****************************源：主BCU 宿：主LCDM（ID：20  8）****************************/
//	TxHeader.ExtId = 0x281;
//	TxData[0]=0xa1;
//	TxData[1]=0xa2;
//	TxData[2]=0xa3;
//	TxData[3]=0xa4;
//	TxData[4]=0xa5;
//	TxData[5]=0xa6;
//	TxData[6]=0xa7;
//	TxData[7]=0xa8;
//	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
//	{
//		/* Transmission request Error */
//		Error_Handler();
//	}
//	
//	/****************************源：主BCU 宿：主LCDM（ID：21  8）****************************/
//	TxHeader.ExtId = 0x2a1;
//	TxData[0]=0xb1;
//	TxData[1]=0xb2;
//	TxData[2]=0xb3;
//	TxData[3]=0xb4;
//	TxData[4]=0xb5;
//	TxData[5]=0xb6;
//	TxData[6]=0xb7;
//	TxData[7]=0xb8;
//	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
//	{
//		/* Transmission request Error */
//		Error_Handler();
//	}
}

//void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
//{
//	
//}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
	unsigned char i=0;
	test1 = 88;
	/* Get RX message */
	if (HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	{
		/* Reception Error */
		Error_Handler();
	}

	/* data check */
	if((RxHeader.IDE == CAN_ID_EXT) && (RxHeader.DLC == 8))
	{
		if(RxHeader.ExtId == 0x2010000)
			for(i=0;i<8;i++)
				rx1[i] = RxData[i];

		else if(RxHeader.ExtId == 0x2210000)
			for(i=0;i<8;i++)
				rx2[i] = RxData[i];		
	
		else if(RxHeader.ExtId == 0x2410000)
			for(i=0;i<8;i++)
				rx3[i] = RxData[i];

//		if(RxHeader.ExtId == 0x261)
//			for(i=0;i<8;i++)
//				rx4[i] = RxData[i];	
//		
//		if(RxHeader.ExtId == 0x281)
//			for(i=0;i<8;i++)
//				rx5[i] = RxData[i];

//		if(RxHeader.ExtId == 0x2a1)
//			for(i=0;i<8;i++)
//				rx6[i] = RxData[i];	
	}
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
