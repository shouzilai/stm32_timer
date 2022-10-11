#include "spi.h"

static u8 SPI1_ReadWriteByte(u8 byte)
{		
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);  	// 等待发送区空
	SPI_I2S_SendData(SPI1, byte);									   	// 发送一个字节  
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 	// 等待接收完一个字节
	return SPI_I2S_ReceiveData(SPI1);								   	// 返回收到的数据 			    
}

void OLED_SPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI1_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_SPI1, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_RES|SPI_PIN_DC|SPI_PIN_CS;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SPI_PIN_CLK|SPI_PIN_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;     //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //设置SPI工作模式:设置为主SPI
    SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                        //选择了串行时钟的稳态:空闲时钟低
    SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                        //数据捕获(采样)于第1个时钟沿
    SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;              		        //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//定义波特率预分频的值:波特率预分频值为256
    SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                    //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI1_InitStructure.SPI_CRCPolynomial = 7;	                            //CRC值计算的多项式
    SPI_Init(SPI1, &SPI1_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
}

void OLED_SPI_WR_Byte(unsigned char data,unsigned char cmd)
{
    if(cmd){
        SPI_DC_H;
    }else{
        SPI_DC_L;
    }
    SPI_CS_L;			 	
	SPI1_ReadWriteByte(data);
    SPI_CS_H;
    SPI_DC_H;
}

