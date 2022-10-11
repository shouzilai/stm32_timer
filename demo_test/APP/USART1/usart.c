#include "usart.h"

extern buffer_fifo_t fifo;

/*����1�жϷ�����*/
void USART1_IRQHandler(void)
{
	u8 res;
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET ) //���յ�����
	{
		res =USART_ReceiveData(USART1);
		if(fifo.free_lvl>0)
		{
            buffer_fifo_write(&fifo,&res,1);                //��¼���յ���ֵ
		}
	}											 
}

///*��ʱ��6�жϷ�����*/
//void TIM6_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)          //��ⶨʱ���жϱ�־λ
//	{
//		USART1_RX_STA |= 1<<15;	                                //��ǽ������
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);             //���TIM6�����жϱ�־
//		TIM_Cmd(TIM6, DISABLE);                                 //�ر�TIM6
//	}
//}
//
//void TIM6_Init(void)
//{
//    //�����ṹ�����
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    //ʹ��TIM7ʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
//    
//	//��ʼ����ʱ��TIM7
//	TIM_TimeBaseStructure.TIM_Period = 499;                     //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler = 7199;                 //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);             //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//    
//    //ʹ�ܶ�ʱ��TIM6�ж�,��������ж�
//	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);
//  	//��ʱ��TIM6ʹ��
//    TIM_Cmd(TIM6, DISABLE);
//    
//    //��ʼ��TIM6 NVIC�ж����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		    //�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	                            //����ָ���Ĳ�����ʼ��NVIC�Ĵ���
//}

void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    //��λUSART1
 	USART_DeInit(USART1);
	//��ʼ��USART1_TX��GPIO�˿�
	GPIO_InitStructure.GPIO_Pin = TX_PIN;                           //�˿ڣ�PA_9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //�ٶȣ�50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         	    //ģʽ�������������
	GPIO_Init(TX_GPIO, &GPIO_InitStructure);                        //�����趨������ʼ��USART_TX
    //��ʼ��USART1_RX��GPIO�˿�
	GPIO_InitStructure.GPIO_Pin = RX_PIN;                           //�˿ڣ�PA_10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;           //ģʽ����������
	GPIO_Init(RX_GPIO, &GPIO_InitStructure);                        //�����趨������ʼ��USART_RX
	//��ʼ��USART NVIC�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;         //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		        //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                                //����ָ���Ĳ�����ʼ��NVIC�Ĵ���
    //��ʼ��USART
	USART_InitStructure.USART_BaudRate = 115200;                    //���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;          //һλֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;             //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); 		                //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //��������1�����ж�
	USART_Cmd(USART1, ENABLE);                    	                //ʹ�ܴ���1
	//��ʼ����ʱ��
//	TIM6_Init();		                                            //��ʼ��ͨ�ö�ʱ��6
//	USART1_RX_STA=0;			                                    //���㴮��1����״̬��־
//	TIM_Cmd(TIM6,DISABLE);		                                    //�رն�ʱ��7
}

/**
 *  @�������ã���USART2������Ϣ
 *  @�����������跢�͵�����(һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�)
 */
void Usart_Send(uint8_t *addr,uint16_t len)
{
	u16 i;
	for( i = 0 ; i < len ; i++ )							        //ѭ����������
	{
	  	while( USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET );//ѭ������,ֱ���������
		USART_SendData(USART1, addr[i]);
	}
}


