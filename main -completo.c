/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7789/st7789.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// Estrutura para representar uma coordenada no plano


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO9 (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9) == 0)
#define BOTAO10 (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10) == 0)
#define BOTAO11 (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11) == 0)
#define BOTAO12 (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12) == 0)

#define LED3_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LED4_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LED5_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LED6_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)

#define LED3_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define LED4_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define LED5_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define LED6_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)

#define DELAY HAL_Delay(2000)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int direcao;
int ColetavelX;
int ColetavelY;
int score = 0;
int scoremax;
int controle = 0;
int velo = 100;
int botao;
int bola1Inix = 83;
int bola1Iniy = 150;
int bola1Finx = 83;
int bola1Finy = 150;

int bola2x = 74;
int bola2y = 150;

int bola3x = 65;
int bola3y = 150;

int bola4x = 56;
int bola4y = 150;

int jogar = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void Menu(void);
void IniciarJogo (void);
void VelocidadeLed (void);
void Controles(void);
void movimento(void);
void desenharbola1(void);
void desenharbola2(void);
void desenharbola3(void);
void desenharbola4(void);
void apagarbola(void);
void colisao(void);
void coletavel(void);
void apagarcoletavel(void);
// Atualiza a posição da cabeça da cobrinha com base na direção atual



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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7789_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //Menu();
	  Jogo();

	  	        }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
int posx = 40;
int posy = 120;
int raio = 5;
/* USER CODE BEGIN 4 */
void Jogo(){
	 posx = 40;
	 posy = 120;
	 raio = 5;

	int contador = 1;

	ST7789_Fill_Color(BLACK);
	ST7789_DrawFilledRectangle(20,40,200,180, WHITE);

	while(contador){
		if(BOTAO11 && posx < 190){
			MVdireita();
		}
		if(BOTAO9 && posx > 20){
			MVesquerda();
			}

		if(BOTAO10){

			contador = 0;
		}
		DesenhaHorizonte();
	}
}
void DesenhaHorizonte(){
	raio =0
	while(true){

		ST7789_DrawFilledCircle(posx + raio, posy, 5, BLACK);

	}

}
void DesenhaVertical(){

	ST7789_DrawFilledCircle(posx , (posy + raio), 5, BLACK);
	ST7789_DrawFilledCircle(posx , (posy + (raio * 3)), 5, BLACK);
	ST7789_DrawFilledCircle(posx , (posy+ (raio * 4)), 5, BLACK);
	ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, BLACK);
	ST7789_DrawFilledCircle(posx, (posy + (raio * 2)), 5, BLACK);
	ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, BLACK);
}

void MVdireita(){
	while(posx < 190){
					ST7789_DrawFilledCircle(posx, posy, 5, WHITE);
					DesenhaHorizonte();
			posx = posx + 5;
			if(BOTAO10){
				ST7789_DrawFilledCircle(posx - (raio * 2), posy, 5, WHITE);
				ST7789_DrawFilledCircle(posx - (raio * 3), posy, 5, WHITE);
				ST7789_DrawFilledCircle((posx - (raio * 4)), (posy), 5, WHITE);
				ST7789_DrawFilledCircle(posx - (raio * 5), posy, 5, WHITE);
				ST7789_DrawFilledCircle((posx - (raio * 6)), (posy), 5, WHITE);
				MVbaixo();
				break;
			}	if(BOTAO12){
				ST7789_DrawFilledCircle(posx - (raio * 2), posy, 5, WHITE);
				ST7789_DrawFilledCircle(posx - (raio * 3), posy, 5, WHITE);
				ST7789_DrawFilledCircle((posx - (raio * 4)), (posy), 5, WHITE);
				ST7789_DrawFilledCircle(posx - (raio * 5), posy, 5, WHITE);
				ST7789_DrawFilledCircle((posx - (raio * 6)), (posy), 5, WHITE);
				MVcima();
				break;
			}
				}

}
void MVesquerda(){

	while(posx > 20){
	ST7789_DrawFilledCircle((posx + (raio * 8)), (posy), 5, WHITE);
	DesenhaHorizonte();
	posx = posx - 5;
	if(BOTAO10){
		ST7789_DrawFilledCircle(posx + (raio * 2), posy, 5, WHITE);
		ST7789_DrawFilledCircle(posx + (raio * 3), posy, 5, WHITE);
		ST7789_DrawFilledCircle((posx + (raio * 4)), (posy), 5, WHITE);
		ST7789_DrawFilledCircle(posx + (raio * 5), posy, 5, WHITE);
		ST7789_DrawFilledCircle((posx + (raio * 6)), (posy), 5, WHITE);
		MVbaixo();
		break;
	}	if(BOTAO12){
		ST7789_DrawFilledCircle(posx + (raio * 2), posy, 5, WHITE);
		ST7789_DrawFilledCircle(posx + (raio * 3), posy, 5, WHITE);
		ST7789_DrawFilledCircle((posx + (raio * 4)), (posy), 5, WHITE);
		ST7789_DrawFilledCircle(posx + (raio * 5), posy, 5, WHITE);
		ST7789_DrawFilledCircle((posx + (raio * 6)), (posy), 5, WHITE);
		MVcima();
		break;
	}
	}
}
void MVcima(){

	while(posy > 40){
	ST7789_DrawFilledCircle(posx, (posy + (raio * 8)), 5, WHITE);
	DesenhaVertical();
	posy = posy - 5;
	if(BOTAO11){
		ST7789_DrawFilledCircle(posx , (posy + (raio * 3)), 5, WHITE);
		ST7789_DrawFilledCircle(posx , (posy+ (raio * 4)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy + (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, WHITE);
		MVdireita();
		break;
	}	if(BOTAO9){
		ST7789_DrawFilledCircle(posx , (posy + (raio * 3)), 5, WHITE);
		ST7789_DrawFilledCircle(posx , (posy+ (raio * 4)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy + (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy+ (raio * 2)), 5, WHITE);
		MVesquerda();
		break;
	}
	}
}
void MVbaixo(){

	while(posy < 220){
	ST7789_DrawFilledCircle((posx + (raio * 8)), (posy), 5, WHITE);
	DesenhaVertical();
	posy = posy + 5;
	if(BOTAO11){
		ST7789_DrawFilledCircle(posx , (posy - (raio * 3)), 5, WHITE);
		ST7789_DrawFilledCircle(posx , (posy - (raio * 4)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy - (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy  - (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy - (raio * 2)), 5, WHITE);
		MVdireita();
		break;
	}	if(BOTAO9){
		ST7789_DrawFilledCircle(posx , (posy - (raio * 3)), 5, WHITE);
		ST7789_DrawFilledCircle(posx , (posy - (raio * 4)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy - (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy - (raio * 2)), 5, WHITE);
		ST7789_DrawFilledCircle(posx, (posy - (raio * 2)), 5, WHITE);
		MVesquerda();
		break;
	}
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
