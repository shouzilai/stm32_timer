#include "oled_spi.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];


//�����Դ浽OLED	
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_SPI_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
		OLED_SPI_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
		OLED_SPI_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
		for(n=0;n<128;n++)
		{
			OLED_SPI_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
		}
  }
}

//��������
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
        {
            OLED_GRAM[n][i]=0;//�����������
        }
    }
	OLED_Refresh();//������ʾ
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���	
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	if(t){OLED_GRAM[x][i]|=n;}
	else
	{
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
		OLED_GRAM[x][i]|=n;
		OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	}
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size1:ѡ������ 6x8/6x12/8x16/12x24
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode)
{
	u8 i,m,temp,size2,chr1;
	u8 x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
		if(size1==8)
        {temp=asc2_0806[chr1][i];} //����0806����
		else if(size1==12)
        {temp=asc2_1206[chr1][i];} //����1206����
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //����1608����
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //����2412����
		else return;
		for(m=0;m<8;m++)
		{
			if(temp&0x01)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp>>=1;
			y++;
		}
		x++;
		if((size1!=8)&&((x-x0)==size1/2))
		{x=x0;y0=y0+8;}
		y=y0;
  }
}

//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
//mode:0,��ɫ��ʾ;1,������ʾ
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x,y,*chr,size1,mode);
		if(size1==8)x+=6;
		else x+=size1/2;
		chr++;
  }
}

//��ʼ��OLED
void OLED_Init(void)
{
    //��ʼ��SPI
    OLED_SPI_Init();
    SPI_CS_L;
    SPI_RES_H;
	delay_ms(100);
    SPI_RES_L;
	delay_ms(100);
    SPI_RES_H;
    
    OLED_SPI_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_SPI_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_SPI_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_SPI_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_SPI_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_SPI_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_SPI_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_SPI_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_SPI_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_SPI_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_SPI_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_SPI_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_SPI_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_SPI_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_SPI_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_SPI_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_SPI_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_SPI_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_SPI_WR_Byte(0x12,OLED_CMD);
	OLED_SPI_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_SPI_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_SPI_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_SPI_WR_Byte(0x02,OLED_CMD);//
	OLED_SPI_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_SPI_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_SPI_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_SPI_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_SPI_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_SPI_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
    
    
//    OLED_SPI_WR_Byte(0xAE,OLED_CMD);    //����ʾ
//	OLED_SPI_WR_Byte(0x20,OLED_CMD);	//�����ڴ�Ѱַģʽ	
//	OLED_SPI_WR_Byte(0x10,OLED_CMD);	//00��ˮƽѰַģʽ;01����ֱѰַģʽ;10��ҳ��Ѱַģʽ(����);11����Ч
//	OLED_SPI_WR_Byte(0xb0,OLED_CMD);	//Ϊҳ��Ѱַģʽ����ҳ�濪ʼ��ַ��0-7
//	OLED_SPI_WR_Byte(0xc8,OLED_CMD);	//����COM���ɨ�跽��
//	OLED_SPI_WR_Byte(0x00,OLED_CMD);    //---���õ��е�ַ
//	OLED_SPI_WR_Byte(0x10,OLED_CMD);    //---���ø��е�ַ
//	OLED_SPI_WR_Byte(0x40,OLED_CMD);    //--������ʼ�е�ַ
//	OLED_SPI_WR_Byte(0x81,OLED_CMD);    //--set contrast control register
//	OLED_SPI_WR_Byte(0xff,OLED_CMD);    //���ȵ��� 0x00~0xff
//	OLED_SPI_WR_Byte(0xa1,OLED_CMD);    //--���ö�����ӳ��0��127
//	OLED_SPI_WR_Byte(0xa6,OLED_CMD);    //--����������ʾ
//	OLED_SPI_WR_Byte(0xa8,OLED_CMD);    //--���ø��ñ�(1 ~ 64)
//	OLED_SPI_WR_Byte(0x3F,OLED_CMD);    //
//	OLED_SPI_WR_Byte(0xa4,OLED_CMD);    //0xa4,�����ѭRAM����;0xa5,Output����RAM����
//	OLED_SPI_WR_Byte(0xd3,OLED_CMD);    //-������ʾ����
//	OLED_SPI_WR_Byte(0x00,OLED_CMD);    //-not offset
//	OLED_SPI_WR_Byte(0xd5,OLED_CMD);    //--������ʾʱ�ӷ�Ƶ/����Ƶ��
//	OLED_SPI_WR_Byte(0xf0,OLED_CMD);    //--���÷���
//	OLED_SPI_WR_Byte(0xd9,OLED_CMD);    //--����pre-chargeʱ��
//	OLED_SPI_WR_Byte(0x22,OLED_CMD);    //
//	OLED_SPI_WR_Byte(0xda,OLED_CMD);    //--����com��ͷ��Ӳ������
//	OLED_SPI_WR_Byte(0x12,OLED_CMD);    //
//	OLED_SPI_WR_Byte(0xdb,OLED_CMD);    //--����vcomh
//	OLED_SPI_WR_Byte(0x20,OLED_CMD);    //0x20,0.77xVcc
//	OLED_SPI_WR_Byte(0x8d,OLED_CMD);    //--����DC-DC
//	OLED_SPI_WR_Byte(0x14,OLED_CMD);    //
//	OLED_SPI_WR_Byte(0xaf,OLED_CMD);    //--��oled���
    
    OLED_Clear();
}

