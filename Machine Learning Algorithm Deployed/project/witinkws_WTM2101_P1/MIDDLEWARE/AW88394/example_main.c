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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdint.h"
#include "aw883xx_init.h"
#include "aw883xx.h"
#include "aw_params.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#if 1
int fputc(int ch, FILE *f)
{
	uint8_t temp[1]={ ch };
	HAL_UART_Transmit(&huart1, temp, 1, 10);
	return 0;
}
#endif
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
int aw_dev0_i2c_write_func(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len)
{
	if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr,
					I2C_MEMADD_SIZE_8BIT, pdata, len, 1000) != HAL_OK){
		return -1;
	} else {
		return 0;
	}
}

int aw_dev0_i2c_read_func(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len)
{
	if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr,
					I2C_MEMADD_SIZE_8BIT, pdata, len, 1000) != HAL_OK) {
		return -1;
	} else {
		return 0;
	}
}

void aw_dev0_reset_gpio_ctl(bool State)
{
	GPIO_PinState PinState = (GPIO_PinState)State;
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0, PinState);
}


int aw_dev1_i2c_write_func(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len)
{
	if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr,
					I2C_MEMADD_SIZE_8BIT, pdata, len, 1000) != HAL_OK){
		return -1;
	} else {
		return 0;
	}
}

int aw_dev1_i2c_read_func(uint16_t dev_addr, uint8_t reg_addr,
				uint8_t *pdata, uint16_t len)
{
	if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr,
					I2C_MEMADD_SIZE_8BIT, pdata, len, 1000) != HAL_OK) {
		return -1;
	} else {
		return 0;
	}
}

void aw_dev1_reset_gpio_ctl(bool State)
{
	GPIO_PinState PinState = (GPIO_PinState)State;
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3, PinState);
}


extern int aw883xx_pid_2049_dev_init(void *aw883xx);


struct aw_init_info init_info[] = {
		{
			.dev = AW_DEV_0,
			.i2c_addr =0x34,
			.re_min = 2000,        /*awinic:If the re_min(ohms) and re_max(ohms) are not set, the default value is used*/
			.re_max = 39000,
			.mix_chip_count = AW_DEV0_MIX_CHIP_NUM,
			.prof_info = g_dev0_prof_info,
			.i2c_read_func = aw_dev0_i2c_read_func,
			.i2c_write_func = aw_dev0_i2c_write_func,
			.reset_gpio_ctl = aw_dev0_reset_gpio_ctl,
			.dev_init_ops = {aw883xx_pid_2049_dev_init},
		},
/*
		{
			.dev = AW_DEV_1,
			.i2c_addr =0x35,
			.re_min = 2000,
			.re_max = 39000,
			.mix_chip_count = AW_DEV1_MIX_CHIP_NUM,
			.prof_info = g_dev1_prof_info,
			.i2c_read_func = aw_dev1_i2c_read_func,
			.i2c_write_func = aw_dev1_i2c_write_func,
			.reset_gpio_ctl = aw_dev1_reset_gpio_ctl,
			.dev_init_ops = {aw883xx_pid_2049_dev_init},
		},
*/
	};
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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */


  /*awinic:Control interface of dev0*/
	/*awinic:initialization*/
	aw883xx_smartpa_init((void *)&init_info[AW_DEV_0]);
	/*awinic:set mode "Music", "aw_params.h" contains id information*/
	aw883xx_set_profile_byname(AW_DEV_0, "Music");

	/*awinic:The platform needs to output I2s first, and then ctl start*/
	aw883xx_ctrl_state(AW_DEV_0, AW_START);

	/*awinic:The platform needs to control the stop first and then stop I2S*/
	aw883xx_ctrl_state(AW_DEV_0, AW_STOP);
	/*awinic:Free the requested memory when PA is not used*/
	//aw883xx_smartpa_deinit(AW_DEV_0);


	/*awinic:Control interface of dev1*/
	//aw883xx_smartpa_init((void *)&init_info[AW_DEV_1]);
	//aw883xx_set_profile_byname(AW_DEV_1, "Music");
	//aw883xx_ctrl_state(AW_DEV_1, AW_START);


	/*awinic:If enable the monitor function, palese enable the timer*/
	//HAL_TIM_Base_Start_IT(&htim3);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/*awinic:If enable the monitor function, palese enable monitor work*/
	//aw883xx_monitor_work(AW_DEV_0);

	/*awinic:If enable the irq function, palese enable irq_handler*/
	//aw883xx_irq_handler(AW_DEV_0);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C2
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*awinic:call aw_irq interface in EXTI*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if (GPIO_Pin == GPIO_PIN_2) {
			//aw883xx_irq_trigger(AW_DEV_0);
		}
}

/*awinic:If enable the monitor function, palese set monitor status in TIM_PeriodElapsedCallback*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim ==(&htim3)) {
		//aw883xx_monitor_set_status(AW_DEV_0);
	}
}

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
