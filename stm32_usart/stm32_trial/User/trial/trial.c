#include "stm32f10x.h"

#define Max_BUFF_Len 18
unsigned char Uart2_Buffer[Max_BUFF_Len];
unsigned int Uart2_Rx = 0;

void USART2_IRQHandler()
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //中断产生
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE); // 清除中断标志

        Uart2_Buffer[Uart2_Rx] = USART_ReceiveData(USART2); // 接收串口1数据到buff缓冲区
        Uart2_Rx++;

        if (Uart2_Buffer[Uart2_Rx - 1] == 0x0a || Uart2_Rx == Max_BUFF_Len) //如果接收到尾标识是换行符（或者等于最大接受数就清空重新接收）
        {
            if (Uart2_Buffer[0] == '+') //检测到头标识是我们需要的
            {
                printf("%s\r\n", Uart2_Buffer); //这里我做打印数据处理
                Uart2_Rx = 0;
            }
            else
            {
                Uart2_Rx = 0; //不是我们需要的数据或者达到最大接收数则开始重新接收
            }
        }
    }
}
// ————————————————           方案一
//
// 版权声明：本文为CSDN博主「可以吃的鱼」的原创文章，遵循CC 0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/qq_35281599/article/details/80299770

void DMA_Config(void)
{
    //---------------------串口功能配置---------------------
    //打开串口对应的外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    //串口发DMA配置
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    // DMA发送中断设置
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // DMA1通道4配置
    DMA_DeInit(DMA1_Channel4);
    //外设地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
    //内存地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_Send_Buffer;
    // dma传输方向单向
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    //设置DMA在传输时缓冲区的长度
    DMA_InitStructure.DMA_BufferSize = 100;
    //设置DMA的外设递增模式，一个外设
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //设置DMA的内存递增模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //外设数据字长
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    //内存数据字长
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    //设置DMA的传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    //设置DMA的优先级别
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    //设置DMA的2个memory中的变量互相访问
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);

    //使能通道4
    // DMA_Cmd(DMA1_Channel4, ENABLE);

    //串口收DMA配置
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    // DMA1通道5配置
    DMA_DeInit(DMA1_Channel5);
    //外设地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
    //内存地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_Rx;
    // dma传输方向单向
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    //设置DMA在传输时缓冲区的长度
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;
    //设置DMA的外设递增模式，一个外设
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //设置DMA的内存递增模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //外设数据字长
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    //内存数据字长
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    //设置DMA的传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    //设置DMA的优先级别
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    //设置DMA的2个memory中的变量互相访问
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    //使能通道5
    DMA_Cmd(DMA1_Channel5, ENABLE);

    //初始化参数
    // USART_InitStructure.USART_BaudRate = DEFAULT_BAUD;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_BaudRate = DEFAULT_BAUD;
    //初始化串口
    USART_Init(USART1, &USART_InitStructure);
    // TXE发送中断,TC传输完成中断,RXNE接收中断,PE奇偶错误中断,可以是多个
    // USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    //中断配置
    USART_ITConfig(USART1, USART_IT_TC, DISABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    //配置UART1中断
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //通道设置为串口1中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //中断占先等级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //中断响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //打开中断
    NVIC_Init(&NVIC_InitStructure);

    //采用DMA方式发送
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    //采用DMA方式接收
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    //启动串口
    USART_Cmd(USART1, ENABLE);
}
