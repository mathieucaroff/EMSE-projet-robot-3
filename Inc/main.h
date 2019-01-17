/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define IR1_in_Pin GPIO_PIN_2
#define IR1_in_GPIO_Port GPIOC
#define IR2_in_Pin GPIO_PIN_3
#define IR2_in_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define IR4_in_Pin GPIO_PIN_4
#define IR4_in_GPIO_Port GPIOC
#define U_Batt_Pin GPIO_PIN_5
#define U_Batt_GPIO_Port GPIOC
#define IR3_in_Pin GPIO_PIN_1
#define IR3_in_GPIO_Port GPIOB
#define DIR2_Pin GPIO_PIN_2
#define DIR2_GPIO_Port GPIOB
#define PWMD_Pin GPIO_PIN_11
#define PWMD_GPIO_Port GPIOB
#define IR1_out_Pin GPIO_PIN_12
#define IR1_out_GPIO_Port GPIOB
#define IR4_out_Pin GPIO_PIN_14
#define IR4_out_GPIO_Port GPIOB
#define IR2_out_Pin GPIO_PIN_15
#define IR2_out_GPIO_Port GPIOB
#define DIR1_Pin GPIO_PIN_8
#define DIR1_GPIO_Port GPIOC
#define IR3_out_Pin GPIO_PIN_12
#define IR3_out_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PWMG_Pin GPIO_PIN_15
#define PWMG_GPIO_Port GPIOA
#define BLE_RX_Pin GPIO_PIN_10
#define BLE_RX_GPIO_Port GPIOC
#define BLE_TX_Pin GPIO_PIN_11
#define BLE_TX_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define ENC1A_Pin GPIO_PIN_4
#define ENC1A_GPIO_Port GPIOB
#define ENC1B_Pin GPIO_PIN_5
#define ENC1B_GPIO_Port GPIOB
#define ENC2A_Pin GPIO_PIN_6
#define ENC2A_GPIO_Port GPIOB
#define ENC2B_Pin GPIO_PIN_7
#define ENC2B_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
