/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include"stdio.h"
#include"string.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define AHT25_ADDR 0x70
#define AHT25_MEASURE_CMD 0xAC

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
I2C_HandleTypeDef hi2c1;
float temperature, humidity;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId SendTaskHandle;
osThreadId ReceiveTaskHandle;
osMessageQId myQueueTempHandle;
/* USER CODE BEGIN PV */
typedef struct
{
float temp;
float humi;
}data;
/* USER CODE END PV */
int p=60000;
typedef enum {
  STATE_INIT,
  STATE_READ_SENSOR,
  STATE_PUBLISH_MQTT,
} state_t;

state_t state = STATE_INIT;
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void Callback(void *argument);
void WE10_Init (void);
void MQTT_Init(void);
/* USER CODE BEGIN PFP */
void read_sensor_values(float *temperature, float *humidity)
{
uint8_t data[6];
uint8_t cmd = AHT25_MEASURE_CMD;
HAL_I2C_Master_Transmit(&hi2c1, AHT25_ADDR,&cmd, 1, HAL_MAX_DELAY);
HAL_Delay(100);
HAL_I2C_Master_Receive(&hi2c1,0x71, data, 6, HAL_MAX_DELAY);
*humidity = ((float)((data[1] << 12) | (data[2] << 4) | (data[3] >> 4))) /
1048576.0 * 100.0;
*temperature = ((float)(((data[3] & 0x0F) << 16) | (data[4] << 8) |
data[5])) / 1048576.0 * 200.0 - 50.0;
}
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
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  WE10_Init();
  MQTT_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueueTemp */
  osMessageQDef(myQueueTemp, 16, uint16_t);
  myQueueTempHandle = osMessageCreate(osMessageQ(myQueueTemp), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of SendTask */
  osThreadDef(SendTask, StartTask02, osPriorityIdle, 0, 128);
  SendTaskHandle = osThreadCreate(osThread(SendTask), NULL);

  /* definition and creation of ReceiveTask */
  osThreadDef(ReceiveTask, StartTask03, osPriorityIdle, 0, 128);
  ReceiveTaskHandle = osThreadCreate(osThread(ReceiveTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}
void StateMachine(void *argument)
{
while(1)
{
switch (state) {
case STATE_INIT:
// Perform initialization tasks if necessary
WE10_Init();
MQTT_Init();
// Transition to the next state
state=STATE_READ_SENSOR;
break;
case STATE_READ_SENSOR:
{
read_sensor_values(&temperature, &humidity);
state=STATE_PUBLISH_MQTT;
}
break;
case STATE_PUBLISH_MQTT:
{
// Receive data from external source
StartTask02(&argument);
StartTask03(&argument);
Callback(&p);
// Transition to the next state
state=STATE_READ_SENSOR;
}
break;
}
}
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */
  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */
  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler =15999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 60000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&htim3, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */
  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */
  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */
  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
	for(;;)
	  {
	    osDelay(1);
	  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	for(;;)
			  {

			    if (xQueueReceive(SendTaskHandle, &temperature, portMAX_DELAY) == pdTRUE)
			    {

			      char buffer[100];

			      sprintf(buffer, "temperature=%.2f\r\n", temperature);
			      HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
			      HAL_Delay(10000);


			      /*********CMD+MQTTPUB ********/
			      		sprintf (&buffer[0], "CMD+MQTTPUB=base/state/temperature,%.2f\r\n",temperature);
			      		HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
			      		HAL_Delay(10000);

			      		//vTaskDelay(pdMS_TO_TICKS(500));
			      		/********CMD+MQTTPUB----->HUMD ********/
			     // HAL_UART_Transmit_IT(&huart2,(uint8_t*)buffer, strlen(buffer));
			    	}
			    if (xQueueReceive(myQueueTempHandle, &humidity, portMAX_DELAY) == pdTRUE)
			    	    {

			    	      char buffer[100];

			    	      sprintf(buffer, "humidity=%.2f\r\n", humidity);
			    	      HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
			    	      HAL_Delay(10000);

			    	      sprintf (&buffer[0], "CMD+MQTTPUB=base/state/humidity,%.2f\r\n",humidity);
			    	      HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
			    	      HAL_Delay(10000);

			    	     // HAL_UART_Transmit_IT(&huart2,(uint8_t*)buffer, strlen(buffer));
			    	    	}

			    }
			    osDelay(1);

  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	char buffer[128]; // Buffer for holding temperature and humidity data
		  HAL_StatusTypeDef status;
		for(;;)
		  {
			  read_sensor_values(&temperature, &humidity);
			  // Format the data into a string
			     snprintf(buffer, sizeof(buffer), "Temperature: %.2f°C, Humidity: %.2f%%\r\n", temperature, humidity);

			     // Transmit the data over UART
			     status = HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

			     if (status != HAL_OK)
			     {
			       // Handle UART transmission error
			     }

			     osDelay(5000);

		  }

  /* USER CODE END StartTask03 */
}
void WE10_Init ()
{
char buffer[128];
/********* CMD+RESET **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+RESET\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(5000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/********* CMD+WIFIMODE=1 **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+WIFIMODE=1\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(2000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/********* CMD+CONTOAP=SSID,PASSWD **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+CONTOAP=harish,9486890765\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
//memset(&buffer[0],0x00,strlen(buffer));
HAL_Delay(5000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/********* CMD?WIFI**********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD?WIFI\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(2000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
}
void MQTT_Init()
{
char buffer[128];
HAL_Delay(2000);
/*********CMD+MQTTNETCFG **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+MQTTNETCFG=dev.rightech.io,1883\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(2000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/*********CMD+MQTTCONCFG **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+MQTTCONCFG=3,harishkumarslm-0c4m89,,,,,,,,,\r\
n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(2000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/*********CMD+MQTTSTART **********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+MQTTSTART=1\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
// memset(&buffer[0],0x00,strlen(buffer));
HAL_Delay(5000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
/*********CMD+MQTTSUB *********/
//memset(&buffer[0],0x00,strlen(buffer));
sprintf (&buffer[0], "CMD+MQTTSUB=base/relay/led1\r\n");
HAL_UART_Transmit_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
HAL_Delay(2000);
HAL_UART_Receive_IT(&huart1, (uint8_t*)buffer, strlen(buffer));
HAL_UART_Transmit_IT(&huart2, (uint8_t*)buffer, strlen(buffer));
}
void Callback(void *argument) {
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
if (htim->Instance == TIM5) {
HAL_IncTick();
}
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
