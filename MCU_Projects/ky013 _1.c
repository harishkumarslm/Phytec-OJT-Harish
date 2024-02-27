#include "stm32f4xx_hal.h"
#include <math.h>

ADC_HandleTypeDef hadc1;
int sensorPin = GPIO_PIN_5; // Change this to the appropriate GPIO pin
double Thermistor(uint16_t RawADC);

void SystemClock_Config(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    // Configure GPIO pin as an analog input
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable GPIOA clock

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = sensorPin; // Assuming you're using GPIOA_PIN5
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Initialize ADC
    __HAL_RCC_ADC1_CLK_ENABLE(); // Enable ADC1 clock

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&hadc1);

    // Configure the channel you are using (e.g., channel 5)
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5; // Change to the appropriate channel
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // Initialize the UART for serial communication
    HAL_UART_MspInit(&huart2); // Replace huart2 with your UART handle
    HAL_UART_Init(&huart2); // Replace huart2 with your UART handle

    while (1) {
        // Read the ADC value
        HAL_ADC_Start(&hadc1);
        if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
            uint16_t readVal = HAL_ADC_GetValue(&hadc1);
            double temp = Thermistor(readVal);

            // Output on the serial interface
            char buffer[50];
            sprintf(buffer, "Current temperature is: %.2f%cC\r\n", temp, 176);
            HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

            HAL_ADC_Stop(&hadc1);
        }
    }
}

// Thermistor function as in your original code
double Thermistor(uint16_t RawADC) {
    double Temp;
    Temp = log(10000.0 * ((4096.0 / RawADC - 1)));
    Temp = 1.0 /(0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
    Temp = Temp - 273.15; // Convert from Kelvin to Celsius
    return Temp;
}

// System clock configuration
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_RCC_DeInit();

    // Configure the main PLL
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    // Configure the CPU, AHB, and APB clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

