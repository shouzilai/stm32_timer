#include "oled_iic.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];

//�����Դ浽OLED	
void OLED_Refresh(void)
{
	for(int i=0;i<8;i++)
	{
		IIC_WriteCmd(0xb0+i); //��������ʼ��ַ
		IIC_WriteCmd(0x02);   //���õ�����ʼ��ַ
		IIC_WriteCmd(0x10);   //���ø�����ʼ��ַ
		for(int j=0;j<128;j++)
		{
			IIC_WriteData(OLED_GRAM[j][i]);
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

//OLED�ĳ�ʼ��
void OLED_Init(void)
{
    //��ʼ��IIC
    OLED_IIC_Init();
	delay_ms(200);
    
    IIC_WriteCmd(0xAE);    //����ʾ
	IIC_WriteCmd(0x20);	//�����ڴ�Ѱַģʽ	
	IIC_WriteCmd(0x10);	//00��ˮƽѰַģʽ;01����ֱѰַģʽ;10��ҳ��Ѱַģʽ(����);11����Ч
	IIC_WriteCmd(0xb0);	//Ϊҳ��Ѱַģʽ����ҳ�濪ʼ��ַ��0-7
	IIC_WriteCmd(0xc8);	//����COM���ɨ�跽��
	IIC_WriteCmd(0x00);    //---���õ��е�ַ
	IIC_WriteCmd(0x10);    //---���ø��е�ַ
	IIC_WriteCmd(0x40);    //--������ʼ�е�ַ
	IIC_WriteCmd(0x81);    //--set contrast control register
	IIC_WriteCmd(0xff);    //���ȵ��� 0x00~0xff
	IIC_WriteCmd(0xa1);    //--���ö�����ӳ��0��127
	IIC_WriteCmd(0xa6);    //--����������ʾ
	IIC_WriteCmd(0xa8);    //--���ø��ñ�(1 ~ 64)
	IIC_WriteCmd(0x3F);    //
	IIC_WriteCmd(0xa4);    //0xa4,�����ѭRAM����;0xa5,Output����RAM����
	IIC_WriteCmd(0xd3);    //-������ʾ����
	IIC_WriteCmd(0x00);    //-not offset
	IIC_WriteCmd(0xd5);    //--������ʾʱ�ӷ�Ƶ/����Ƶ��
	IIC_WriteCmd(0xf0);    //--���÷���
	IIC_WriteCmd(0xd9);    //--����pre-chargeʱ��
	IIC_WriteCmd(0x22);    //
	IIC_WriteCmd(0xda);    //--����com��ͷ��Ӳ������
	IIC_WriteCmd(0x12);    //
	IIC_WriteCmd(0xdb);    //--����vcomh
	IIC_WriteCmd(0x20);    //0x20,0.77xVcc
	IIC_WriteCmd(0x8d);    //--����DC-DC
	IIC_WriteCmd(0x14);    //
	IIC_WriteCmd(0xaf);    //--��oled���
    OLED_Clear();
}

