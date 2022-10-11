#include "oled_iic.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];

//更新显存到OLED	
void OLED_Refresh(void)
{
	for(int i=0;i<8;i++)
	{
		IIC_WriteCmd(0xb0+i); //设置行起始地址
		IIC_WriteCmd(0x02);   //设置低列起始地址
		IIC_WriteCmd(0x10);   //设置高列起始地址
		for(int j=0;j<128;j++)
		{
			IIC_WriteData(OLED_GRAM[j][i]);
		}
  }
}

//清屏函数
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
			{
			 OLED_GRAM[n][i]=0;//清除所有数据
			}
  }
	OLED_Refresh();//更新显示
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空	
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


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size1:选择字体 6x8/6x12/8x16/12x24
//mode:0,反色显示;1,正常显示
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode)
{
	u8 i,m,temp,size2,chr1;
	u8 x0=x,y0=y;
	if(size1==8)size2=6;
	else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(size1==8)
			  {temp=asc2_0806[chr1][i];} //调用0806字体
		else if(size1==12)
        {temp=asc2_1206[chr1][i];} //调用1206字体
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //调用1608字体
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //调用2412字体
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


//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
//mode:0,反色显示;1,正常显示
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLED_ShowChar(x,y,*chr,size1,mode);
		if(size1==8)x+=6;
		else x+=size1/2;
		chr++;
  }
}

//OLED的初始化
void OLED_Init(void)
{
    //初始化IIC
    OLED_IIC_Init();
	delay_ms(200);
    
    IIC_WriteCmd(0xAE);    //开显示
	IIC_WriteCmd(0x20);	//设置内存寻址模式	
	IIC_WriteCmd(0x10);	//00，水平寻址模式;01，垂直寻址模式;10，页面寻址模式(重置);11，无效
	IIC_WriteCmd(0xb0);	//为页面寻址模式设置页面开始地址，0-7
	IIC_WriteCmd(0xc8);	//设置COM输出扫描方向
	IIC_WriteCmd(0x00);    //---设置低列地址
	IIC_WriteCmd(0x10);    //---设置高列地址
	IIC_WriteCmd(0x40);    //--设置起始行地址
	IIC_WriteCmd(0x81);    //--set contrast control register
	IIC_WriteCmd(0xff);    //亮度调节 0x00~0xff
	IIC_WriteCmd(0xa1);    //--设置段重新映射0到127
	IIC_WriteCmd(0xa6);    //--设置正常显示
	IIC_WriteCmd(0xa8);    //--设置复用比(1 ~ 64)
	IIC_WriteCmd(0x3F);    //
	IIC_WriteCmd(0xa4);    //0xa4,输出遵循RAM内容;0xa5,Output忽略RAM内容
	IIC_WriteCmd(0xd3);    //-设置显示抵消
	IIC_WriteCmd(0x00);    //-not offset
	IIC_WriteCmd(0xd5);    //--设置显示时钟分频/振荡器频率
	IIC_WriteCmd(0xf0);    //--设置分率
	IIC_WriteCmd(0xd9);    //--设置pre-charge时期
	IIC_WriteCmd(0x22);    //
	IIC_WriteCmd(0xda);    //--设置com大头针硬件配置
	IIC_WriteCmd(0x12);    //
	IIC_WriteCmd(0xdb);    //--设置vcomh
	IIC_WriteCmd(0x20);    //0x20,0.77xVcc
	IIC_WriteCmd(0x8d);    //--设置DC-DC
	IIC_WriteCmd(0x14);    //
	IIC_WriteCmd(0xaf);    //--打开oled面板
    OLED_Clear();
}

