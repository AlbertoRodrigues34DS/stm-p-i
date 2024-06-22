/* USER CODE BEGIN Header */
/**
  **************************
  * @file           : main.c
  * @brief          : Main program body
  **************************
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
  **************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7789\st7789.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO9 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO10 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO11 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO12 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)

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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
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
	  Menu();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Menu(void)
    {
	int escolha=0;
    	ST7789_Fill_Color(GREEN);
    	ST7789_WriteString(50, 10, "SNAKEGAME", Font_16x26 , WHITE, BLACK);
    	ST7789_WriteString(40, 80, "PA9 - Jogar!!", Font_11x18, WHITE, BLACK);
    	ST7789_WriteString(40, 120, "PA10 - Velocidade", Font_11x18, WHITE, BLACK);
    	HAL_Delay(2000);

    	while(escolha==0)
    	{
    	if (BOTAO9 == 0 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 1) {
    		//InicarJogo();
    		escolha=1;
    	}

    	else if (BOTAO9 == 1 && BOTAO10 == 0 && BOTAO11 == 1 && BOTAO12 == 1) {
    	    escolha=2;
    	  }

    	    	}
    	switch (escolha) {
    		case 1:
    	    IniciarJogo();
    		break;

    		case 2:
    		VelocidadeLed();
    		break;



    	}
    }

void IniciarJogo (void) {
	jogar = 0;

	bola1Inix = 82;
	bola1Iniy = 150;
	bola1Finx = 82;
	bola1Finy = 150;

	bola2x = 73;
	bola2y = 150;

	bola3x = 64;
	bola3y = 150;

	bola4x = 55;
	bola4y = 150;
	ColetavelX = (rand() % 166) + 34;
    ColetavelY = (rand() % 150) + 80;
	 ST7789_Fill_Color(RED);
	 ST7789_WriteString(50, 25, "SCORE = ", Font_16x26 , WHITE, RED);
	 ST7789_WriteChar(170, 25, score, Font_16x26 , WHITE, YELLOW);
	 ST7789_DrawFilledRectangle(34, 80, 170, 150, BLACK	);
	 desenharbola1();
	 desenharbola2();
	 desenharbola3();
	 desenharbola4();
	 coletavel();
	 movimento();

     controle  = 1;


 }
void movimento(void) {
    while(jogar == 0) {
        ST7789_WriteChar(170, 25, score + '0', Font_16x26 , WHITE, RED);

        if(BOTAO11 == 0) {
            direcao = 1;
        } else if(BOTAO12 == 0) {
            direcao = 2;
        } else if(BOTAO9 == 0) {
            direcao = 3;
        } else if(BOTAO10 == 0) {
            direcao = 4;
        }

        apagarcoletavel();
        colisao();

        switch (direcao) {
            case 1:
                bola1Finx = bola1Inix + 10;
                break;
            case 2:
                bola1Finy = bola1Iniy - 10;
                break;
            case 3:
                bola1Finx = bola1Inix - 10;
                break;
            case 4:
                bola1Finy = bola1Iniy + 10;
                break;
        }

        apagarbola();
        bola4x = bola3x;
        bola4y = bola3y;
        desenharbola4();
        bola3x = bola2x;
        bola3y = bola2y;
        desenharbola3();
        bola2x = bola1Inix;
        bola2y = bola1Iniy;
        desenharbola2();
        bola1Inix = bola1Finx;
        bola1Iniy = bola1Finy;
        desenharbola1();
    }
}

void colisao(void){


     if(bola1Inix < 41 || bola1Inix > 200 || bola1Iniy < 81 || bola1Iniy > 227){
	 ST7789_Fill_Color(RED);
	 ST7789_WriteString(50, 30, " Derrota ", Font_16x26 , WHITE, RED);
	 ST7789_WriteString(50, 100, "SCORE: ", Font_16x26 , WHITE, RED);
	 ST7789_WriteChar(170, 100, score + '0', Font_16x26 , WHITE, RED);
	 ST7789_WriteString(60, 190, "PA12 - MENU", Font_11x18 , WHITE, RED);

	 while(1){

	 	 		if (BOTAO12 == 0) {
	 	 			jogar = 1;
	 	 			return Menu();
	 	 			break;
	 	 		}
	 	 }
     }
}
void apagarbola(void){

	ST7789_DrawFilledCircle(bola4x, bola4y, 5, BLACK);
    HAL_Delay(velo);

}
void desenharbola1(void){

		ST7789_DrawFilledCircle(bola1Inix, bola1Iniy, 5, GREEN);
		HAL_Delay(velo);
}
void desenharbola2 (void){

		ST7789_DrawFilledCircle(bola2x, bola2y, 5, WHITE);
		HAL_Delay(velo);
}
void desenharbola3 (void){

		ST7789_DrawFilledCircle(bola3x,bola3y, 5, WHITE);
		HAL_Delay(velo);
}
void desenharbola4 (void){

		ST7789_DrawFilledCircle(bola4x,bola4y, 5, WHITE);
		HAL_Delay(velo);
}

void coletavel(void) {
	ColetavelX = (rand() % 166) + 34;
	ColetavelY = (rand() % 150) + 80;

	ST7789_DrawFilledCircle(ColetavelX,ColetavelY, 5, YELLOW);
	HAL_Delay(100);

}

void apagarcoletavel(void) {
	if(ColetavelX - 8 <= bola1Inix && bola1Inix <= ColetavelX + 8 && ColetavelY - 8 <= bola1Iniy && bola1Iniy <= ColetavelY + 8 ) {
	ST7789_DrawFilledCircle(ColetavelX,ColetavelY, 5, BLACK);
	coletavel();
	HAL_Delay(100);
	score += 1;
	}
}

void VelocidadeLed(void) {

	ST7789_Fill_Color(BLUE);
	ST7789_WriteString(30, 20, "Velocidade: ", Font_16x26, WHITE, BLUE);
	ST7789_WriteString(40, 80, "PA9 - LESMA ",Font_11x18, WHITE, BLUE);
	ST7789_WriteString(40, 120, "PA10 - FRANTCHESCO ", Font_11x18, WHITE, BLUE);
	ST7789_WriteString(40, 160, "PA11 - MARQUINHOS", Font_11x18, WHITE, BLUE);
	ST7789_WriteString(40, 200, "PA12 - CONFIRME ", Font_11x18, WHITE, BLUE);

    LED3_LIGA;
	do {
	if (BOTAO9 == 0) {
		LED3_LIGA;
		LED4_DESLIGA;
	    LED5_DESLIGA;
	    velo = 50;
	}

	else if (BOTAO10 == 0) {
		LED3_LIGA;
		LED4_LIGA;
		LED5_DESLIGA;
		velo = 40;
	}

	else if (BOTAO11 == 0) {
		LED3_LIGA;
		LED4_LIGA;
		LED5_LIGA;
		velo = 30;
		}

	} while (BOTAO12 == 1);

	LED3_DESLIGA;
	LED4_DESLIGA;
    LED5_DESLIGA;
    return;
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

/******** (C) COPYRIGHT STMicroelectronics **END OF FILE*/
