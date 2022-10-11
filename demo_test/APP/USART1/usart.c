#include "usart.h"

extern buffer_fifo_t fifo;

/*串口1中断服务函数*/
void USART1_IRQHandler(void)
{
	u8 res;
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET ) //接收到数据
	{
		res =USART_ReceiveData(USART1);
		if(fifo.free_lvl>0)
		{
            buffer_fifo_write(&fifo,&res,1);                //记录接收到的值
		}
	}											 
}

///*定时器6中断服务函数*/
//void TIM6_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)          //检测定时器中断标志位
//	{
//		USART1_RX_STA |= 1<<15;	                                //标记接收完成
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);             //清除TIM6更新中断标志
//		TIM_Cmd(TIM6, DISABLE);                                 //关闭TIM6
//	}
//}
//
//void TIM6_Init(void)
//{
//    //创建结构体变量
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    //使能TIM7时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
//    
//	//初始化定时器TIM7
//	TIM_TimeBaseStructure.TIM_Period = 499;                     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler = 7199;                 //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
//	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);             //根据指定的参数初始化TIMx的时间基数单位
//    
//    //使能定时器TIM6中断,允许更新中断
//	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);
//  	//定时器TIM6使能
//    TIM_Cmd(TIM6, DISABLE);
//    
//    //初始化TIM6 NVIC中断优先级
//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		    //子优先级2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	                            //根据指定的参数初始化NVIC寄存器
//}

void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    //复位USART1
 	USART_DeInit(USART1);
	//初始化USART1_TX的GPIO端口
	GPIO_InitStructure.GPIO_Pin = TX_PIN;                           //端口：PA_9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //速度：50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         	    //模式：复用推挽输出
	GPIO_Init(TX_GPIO, &GPIO_InitStructure);                        //根据设定参数初始化USART_TX
    //初始化USART1_RX的GPIO端口
	GPIO_InitStructure.GPIO_Pin = RX_PIN;                           //端口：PA_10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;           //模式：浮空输入
	GPIO_Init(RX_GPIO, &GPIO_InitStructure);                        //根据设定参数初始化USART_RX
	//初始化USART NVIC中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;         //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		        //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                //根据指定的参数初始化NVIC寄存器
    //初始化USART
	USART_InitStructure.USART_BaudRate = 115200;                    //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;          //一位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;             //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); 		                //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //开启串口1接收中断
	USART_Cmd(USART1, ENABLE);                    	                //使能串口1
	//初始化定时器
//	TIM6_Init();		                                            //初始化通用定时器6
//	USART1_RX_STA=0;			                                    //清零串口1接收状态标志
//	TIM_Cmd(TIM6,DISABLE);		                                    //关闭定时器7
}

/**
 *  @函数作用：给USART2发送消息
 *  @函数参数：需发送的数据(一次发送数据不超过USART2_MAX_SEND_LEN字节)
 */
void Usart_Send(uint8_t *addr,uint16_t len)
{
	u16 i;
	for( i = 0 ; i < len ; i++ )							        //循环发送数据
	{
	  	while( USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET );//循环发送,直到发送完毕
		USART_SendData(USART1, addr[i]);
	}
}


