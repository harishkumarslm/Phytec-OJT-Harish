#include "stm32f4xx.h"
#include "stdio.h"
#define ONE_BYTE_REG_ADDR 0x01
#define TWO_BYTE_REG_ADDR 0x02
// Function to initialize OV7670 camera
void OV7670_Init(void)
{
    // Add your camera initialization code here
    void MCO1_Init(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;

 RCC_ClockSecuritySystemCmd(ENABLE);

 /* Enable GPIOs clocks */
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

 GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);

 /* Configure MCO (PA8) */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 GPIO_Init(GPIOA, &GPIO_InitStructure);

 RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_4);
}

void Hardware_InitI2C(void)
{

 GPIO_InitTypeDef GPIO_InitStructure; // this is for the GPIO pins used as I2C1SDA and I2C1SCL
 I2C_InitTypeDef I2C_InitStructure; // this is for the I2C1 initilization

 /* enable APB1 peripheral clock for I2C1*/
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

 /* enable the peripheral clock for the pins used by
  PB6 for I2C SCL and PB9 for I2C1_SDL*/
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

 /* This sequence sets up the I2C1SDA and I2C1SCL pins
  * so they work correctly with the I2C1 peripheral
  */
 GPIO_StructInit(&GPIO_InitStructure);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; // Pins 10(I2C1_SCL) and 11(I2C1_SDA)
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // the pins are configured as alternate function so the USART peripheral has access to them
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;// this defines the IO speed and has nothing to do with the baudrate!
 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;// this defines the output type as open drain
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
 GPIO_Init(GPIOB, &GPIO_InitStructure);// now all the values are passed to the GPIO_Init()


 /* The I2C1_SCL and I2C1_SDA pins are now connected to their AF
  * so that the I2C1 can take over control of the
  * pins
  */
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1); //
 GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);

  /* Configure I2C1 */
  I2C_StructInit(&I2C_InitStructure);
  I2C_DeInit(I2C1);

  /* Enable the I2C peripheral */
  I2C_Cmd(I2C1, ENABLE);

  /* Set the I2C structure parameters */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000;
  /* I2C Peripheral Enable */
I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE);
  /* Initialize the I2C peripheral w/ selected parameters */
  I2C_Init(I2C1,&I2C_InitStructure);
 I2C_Cmd(I2C1, ENABLE);


}

int i2c_send_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len)
{
  int timeout = 0x7FFFFF;
  int ret = 0;
         /* send i2c*/
  I2C_GenerateSTART(I2C1, ENABLE);
  while( !I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 1;
    goto exit;
   }
  }
  I2C_Send7bitAddress(I2C1, slave_addr, I2C_Direction_Transmitter);
  while(!(I2C1->SR1 & (1 << 1))); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 2;
    goto exit;
   }
  }
  while(!(I2C1->SR2 & (1 << 2)));   // check TRA bit
  {
   if ((timeout--) == 0)
   {
    ret = 3;
    goto exit;
   }
  }

  /* 2 byte reg address */
  if(addr_len == TWO_BYTE_REG_ADDR)
  {
   // MSB
   I2C_SendData(I2C1, (0xFF & (reg_addr >> 8)) );
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 4;
    goto exit;
   }
   }

   // LSB
   I2C_SendData(I2C1, (0xFF & reg_addr));
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 5;
    goto exit;
   }
   }

  }
  /* 1 byte reg address */
  else
  {
   I2C_SendData(I2C1, (0xFF & reg_addr));
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 6;
    goto exit;
   }
   }
  }

  I2C_SendData(I2C1, *data);
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  {
//   if ((timeout--) == 0)
   {
    ret = 7;
    goto exit;
   }
  }

                exit:
  I2C_GenerateSTOP(I2C1, ENABLE);
  return ret;
}
int u8;
int i2c_receive_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len)
{
  int timeout = 0x7FFFFF;
  int ret = 0;
   /* send i2c*/
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 1;
    goto exit;
   }
  }

  I2C_Send7bitAddress(I2C1, slave_addr, I2C_Direction_Transmitter);
  while(!(I2C1->SR1 & (1 << 1))); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 2;
    goto exit;
   }
  }

  while(!(I2C1->SR2 & (1 << 2)));   // check TRA bit
  {
   if ((timeout--) == 0)
   {
    ret = 3;
    goto exit;
   }
  }

  /* 2 byte reg address */
  if(addr_len == TWO_BYTE_REG_ADDR)
  {
   // MSB
   I2C_SendData(I2C1, (0xFF & (reg_addr >> 8)) );
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 4;
    goto exit;
   }
  }

   // LSB
   I2C_SendData(I2C1, (0xFF & reg_addr));
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 5;
    goto exit;
   }
  }
  }

  /* 1 byte reg address */
  else
  {
   I2C_SendData(I2C1, (0xFF & reg_addr));
   while(!(I2C1->SR1 & (1 << 7)));
   {
   if ((timeout--) == 0)
   {
    ret = 6;
    goto exit;
   }
  }
  }

  I2C_GenerateSTOP(I2C1, ENABLE);
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
  {
   if ((timeout--) == 0)
   {
    ret = 7;
    goto exit;
   }
  }
  I2C_Send7bitAddress(I2C1, slave_addr, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // check ADDR bit
  {
   if ((timeout--) == 0)
   {
    ret = 8;
    goto exit;
   }
  }


  I2C_AcknowledgeConfig(I2C1, DISABLE);
                /* Send STOP Condition */
                I2C_GenerateSTOP(I2C1, ENABLE);

  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
  {
   if ((timeout--) == 0)
   {
    ret = 10;
    goto exit;
   }
  }

  *data = I2C_ReceiveData(I2C1);
  I2C_AcknowledgeConfig(I2C1, ENABLE);
  return ret;

exit:
  I2C_GenerateSTOP(I2C1, ENABLE);
  return ret;
}
    // This may involve configuring I2C, camera registers, etc.
    int camera_read_reg(u8 reg, u8* data)
{
 return i2c_receive_data(0x42, (u16) reg, data, ONE_BYTE_REG_ADDR);
}
/*******************************************************************************/
int camera_write_reg(u8 reg, u8* data)
{
 return i2c_send_data(0x43, (u16) reg, data, ONE_BYTE_REG_ADDR);
}

int camera_config()
{
 int ret = 0;
 u8 data = 0;
 sprintf(&tempBuff[0],"CAMERA CONFIGURING\r\n");send(&tempBuff[0]);


 ret = camera_read_reg(0x12, &data); //Reset all registers
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0x80;
 ret = camera_write_reg(0x12, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 ret = camera_read_reg(0x12, &data); //output format to qcif
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0xA;               //yuv enabled
 ret = camera_write_reg(0x12, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 ret = camera_read_reg(0x11, &data); //Set PCLK
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0x8;
 ret = camera_write_reg(0x11, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 ret = camera_read_reg(0x04, &data); //Set qqcif
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0x28;
 ret = camera_write_reg(0x04, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);

 ret = camera_read_reg(0x3A, &data); //Set manual UV values
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0x1C;
 ret = camera_write_reg(0x3A, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);

 ret = camera_read_reg(0x67, &data); //Set manual U value
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0xFF;
 ret = camera_write_reg(0x67, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);

 ret = camera_read_reg(0x68, &data); //Set manual V value
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
 data = 0x0;
 ret = camera_write_reg(0x68, &data);
  if(ret < 0)
  return ret;
 Delay(0xFFFF);
//      ret = camera_read_reg(0x40, &data); //Set out put data range
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  data = 0xC0;
//  ret = camera_write_reg(0x40, &data);
//   if(ret < 0)
//   return ret;
//  Delay(10);
//
//  ret = camera_read_reg(0x17, &data); //Set HSTART 0
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  data = 0x14;
//  ret = camera_write_reg(0x17, &data);
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  ret = camera_read_reg(0x18, &data); //Set HSTOP 40
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  data = 0x3C;
//  ret = camera_write_reg(0x18, &data);
//   if(ret < 0)
//   return ret;
//  Delay(10);
// //
//  ret = camera_read_reg(0x19, &data); //Set VSTART 20  We cxan set number of raws
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  data = 0x14;
//  ret = camera_write_reg(0x19, &data);
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  ret = camera_read_reg(0x1A, &data); //Set VSTOP 40
//   if(ret < 0)
//   return ret;
//  Delay(10);
//  data = 0x28;
//  ret = camera_write_reg(0x1A, &data);
//   if(ret < 0)
//   return ret;
//  Delay(10);

sprintf(&tempBuff[0],"CAMERA CONFIGURING DONE\r\n");send(&tempBuff[0]);
return ret;
}
}

// Function to capture an image from OV7670 camera
void OV7670_CaptureImage(void)
{
    // Add your code to capture an image from the camera

    #define RAW 72
#define COLUMNS 80  //I got only 80 columns instead of 88 columns
#define BYTESPERPIX 2
void DCMI_Configure(void)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
  /* GPIOD Periph clock enable */
 RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

   /* B7: VSYNC*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
    /* A4: HSYNC*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
    /* A6: PCLK*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
    /* C6: data0*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
    /* C7: data1*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);
    /* C8: data2*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
    /* C9: data3*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
    /* E4: data4*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);
    /* B6: data5*/
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
    /* E5: data6*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
    /* E6: data7*/
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);
 /* DCMI GPIO configuration */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOE, &GPIO_InitStructure);


      /* DCMI configuration */

      DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
      DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
      DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
      DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
      DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
      DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
      DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;



      DCMI_Init(&DCMI_InitStructure);


     //DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
     //DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
     //DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
     //DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
     //DCMI_ITConfig(DCMI_IT_ERR, ENABLE);



      /* Configures the DMA2 to transfer Data from DCMI */

      /* DMA2 Stream1 Configuration */
      DMA_DeInit(DMA2_Stream1);

      DMA_StructInit(&DMA_InitStructure);

      DMA_InitStructure.DMA_Channel = DMA_Channel_1;
      DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)(&DCMI->DR);
      DMA_InitStructure.DMA_Memory0BaseAddr =  (uint32_t)frame_buffer;
      DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
      DMA_InitStructure.DMA_BufferSize = ROW*COLUMNS*BYTESPERPIX/4;/* size of image in bytes/4 */
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
      DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
      DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
      DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
      DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
      DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
      DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
      DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
      DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
      DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);
      DMA_ITConfig(DMA2_Stream1, DMA_IT_TE, ENABLE);

      /* DMA2 IRQ channel Configuration */

NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

DMA_Cmd(DMA2_Stream1, ENABLE);

DCMI_Cmd(ENABLE);
DCMI_CaptureCmd(ENABLE);





}

void DMA2_Stream1_IRQHandler(void)
{
 static  int K;
  //Test on DMA2 Channel1 Transfer Complete interrupt
  if(DMA_GetITStatus(DMA2_Stream1,DMA_IT_TCIF1) ==  SET)
  {
  frame_flag = 1;//when frame_flag =1,all the data will be send through serial port in main function while loop
    DMA_ClearITPendingBit(DMA2_Stream1,DMA_IT_TCIF1);
  }
  if(DMA_GetITStatus(DMA2_Stream1,DMA_IT_TEIF1) ==  SET)
  {
    sprintf(&tempBuff[0]," Dma error \r\n");send(&tempBuff[0]);
    DMA_ClearITPendingBit(DMA2_Stream1,DMA_IT_TEIF1);
  }
}

void DCMI_IRQHandler(void)
{
 static volatile int line,col,i,j = 0;
    if(DCMI_GetFlagStatus(DCMI_FLAG_FRAMERI) == SET)
    {
   sprintf(&tempBuff[0],"Frame got\r\n");send(&tempBuff[0]);
   DCMI_ClearFlag(DCMI_FLAG_FRAMERI);
    }
   if(DCMI_GetFlagStatus(DCMI_FLAG_OVFRI) == SET)
    {
   sprintf(&tempBuff[0],"overflow\r\n");send(&tempBuff[0]);
   DCMI_ClearFlag(DCMI_FLAG_OVFRI);
    }
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;

}
    // This may involve reading data from the camera's FIFO buffer or using DMA
}

int main(void)
{
    // Initialize the OV7670 camera
    OV7670_Init();

    // Set up USART or UART for serial communication
    void MCO1_Init(void);
    void Hardware_InitI2C(void) ;
    int i2c_send_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len);
    int i2c_receive_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len);
    // Configure appropriate baud rate, word length, etc.
    int camera_read_reg(u8 reg, u8* data);
    int camera_write_reg(u8 reg, u8* data);
    int camera_config();
    void DCMI_Configure(void);
    void DMA2_Stream1_IRQHandler(void);
    void DCMI_IRQHandler(void);
    // Enable USART or UART interrupt for receiving data

    // Start capturing images
    OV7670_CaptureImage();
    while (1)
  {
  if( frame_flag == 1)
  {
    show_image();
    frame_flag = 0;
  }
  }
}



void show_image(void)
  {
   for( K =0;K< WIDTH*HEIGHT*BYTES_PER_PIXEL/4;K++)
   {
    {
    sprintf(&tempBuff[0],"%d \n",frame_buffer[4*K+1]);send_no_new_line(&tempBuff[0]);
    sprintf(&tempBuff[0],"%d \n",frame_buffer[4*K+3]);send_no_new_line(&tempBuff[0]);
    }
    if ((K+1)%40 == 0 )
    {
     sprintf(&tempBuff[0],";\r\n");send(&tempBuff[0]);
    }
   }
  }


}
