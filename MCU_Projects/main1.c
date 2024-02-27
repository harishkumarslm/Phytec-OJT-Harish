#include "main.h"
#include "cmsis_os.h"
#include"stdio.h"
#include"string.h"
#define AHT25_ADDR 0x70
#define AHT25_MEASURE_CMD 0xAC
float temperature, humidity;
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim2;
/* Definitions for SendTask */
osThreadId_t SendTaskHandle;
const osThreadAttr_t SendTask_attributes = {.name = "SendTask",.stack_size = 128 * 4,.priority = (osPriority_t) osPriorityNormal,};
/* Definitions for RecieveTask */
osThreadId_t RecieveTaskHandle;
const osThreadAttr_t RecieveTask_attributes = {.name = "RecieveTask",.stack_size = 128 * 4,.priority = (osPriority_t) osPriorityLow,};
/* Definitions for myQueueTemp */
osMessageQueueId_t myQueueTempHandle;
const osMessageQueueAttr_t myQueueTemp_attributes = {.name = "myQueueTemp"};
/* Definitions for myTimer */
osTimerId_t myTimerHandle;
const osTimerAttr_t myTimer_attributes = {.name = "myTimer"};
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
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);

void Send_Task(void *argument);
void Recieve_Task(void *argument);
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
*humidity = ((float)((data[1] << 12) | (data[2] << 4) | (data[3] >> 4))) /1048576.0 * 100.0;
*temperature = ((float)(((data[3] & 0x0F) << 16) | (data[4] << 8) |data[5])) / 1048576.0 * 200.0 - 50.0;
}
int main(void)
{
HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
MX_USART2_UART_Init();
MX_I2C1_Init();
MX_TIM2_Init();
MX_USART1_UART_Init();
WE10_Init();
MQTT_Init();
osKernelInitialize();
myTimerHandle = osTimerNew(Callback, osTimerPeriodic, NULL,&myTimer_attributes);
myQueueTempHandle = osMessageQueueNew (256, sizeof(uint16_t),&myQueueTemp_attributes);
SendTaskHandle = osThreadNew(Send_Task, NULL, &SendTask_attributes);
RecieveTaskHandle = osThreadNew(Recieve_Task, NULL, &RecieveTask_attributes);
osKernelStart();
while (1)
{
}
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
Send_Task(&argument);
Recieve_Task(&argument);
Callback(&p);
// Transition to the next state
state=STATE_READ_SENSOR;
}
break;
}
}
}
static void MX_TIM2_Init(void)
{
/* USER CODE BEGIN TIM2_Init 0 */
/* USER CODE END TIM2_Init 0 */
TIM_SlaveConfigTypeDef sSlaveConfig = {0};
TIM_MasterConfigTypeDef sMasterConfig = {0};
/* USER CODE BEGIN TIM2_Init 1 */
/* USER CODE END TIM2_Init 1 */
htim2.Instance = TIM2;
htim2.Init.Prescaler = 15999;
htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
htim2.Init.Period = 60000;
htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
{
Error_Handler();
}
sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
sSlaveConfig.InputTrigger = TIM_TS_ITR0;
if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
{
Error_Handler();
}
sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) !=
{
Error_Handler();
}
/* USER CODE BEGIN TIM2_Init 2 */
/* USER CODE END TIM2_Init 2 */
HAL_OK )
}
void SystemClock_Config(void)

{
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
__HAL_RCC_PWR_CLK_ENABLE();
__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
RCC_OscInitStruct.HSIState = RCC_HSI_ON;
RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
{
Error_Handler();
}
RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
{
Error_Handler();
}
}
static void MX_I2C1_Init(void)
{
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
}
static void MX_USART1_UART_Init(void)
{
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
}
static void MX_USART2_UART_Init(void)
{
28Project code
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
}
static void MX_GPIO_Init(void)
{
__HAL_RCC_GPIOA_CLK_ENABLE();
__HAL_RCC_GPIOB_CLK_ENABLE();
}
void Send_Task(void *argument)
{
data DatatoSend;
while (1) {
read_sensor_values(&temperature, &humidity);
DatatoSend.temp = temperature;
DatatoSend.humi = humidity;
osMessageQueuePut(myQueueTempHandle, &DatatoSend, 0, 0);
osDelay(1000); // Delay for 1000 milliseconds (1 second) before the
next iteration
}
}
void Recieve_Task(void *argument)
{
data retvalue;
for(;;)
{
osMessageQueueGet(myQueueTempHandle,&retvalue,NULL,osWaitForever);
char buffer[128];
sprintf (&buffer[0], "CMD+MQTTPUB=base/state/temperature,%.2f\r\n",retvalue.humi);
HAL_UART_Transmit(&huart2, (uint8_t*)buffer,strlen(buffer),1000);
sprintf (&buffer[0], "CMD+MQTTPUB=base/state/temperature,%.2f\r\n",retvalue.temp);
HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer),1000);
HAL_TIM_Base_Start_IT(&htim2);
}
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
sprintf (&buffer[0], "CMD+CONTOAP=MD ARIF,1234567890\r\n");
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
sprintf (&buffer[0], "CMD+MQTTCONCFG=3,mqtt-arifm4348-ud8eo8,,,,,,,,,\r\n");
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
void Error_Handler(void)
{
__disable_irq();
while (1)
{
}
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
