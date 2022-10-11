#include "spi.h"

static u8 SPI1_ReadWriteByte(u8 byte)
{		
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);  	// �ȴ���������
	SPI_I2S_SendData(SPI1, byte);									   	// ����һ���ֽ�  
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 	// �ȴ�������һ���ֽ�
	return SPI_I2S_ReceiveData(SPI1);								   	// �����յ������� 			    
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

    SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;     //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //����SPI����ģʽ:����Ϊ��SPI
    SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                        //ѡ���˴���ʱ�ӵ���̬:����ʱ�ӵ�
    SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                        //���ݲ���(����)�ڵ�1��ʱ����
    SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;              		        //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                    //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI1_InitStructure.SPI_CRCPolynomial = 7;	                            //CRCֵ����Ķ���ʽ
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

