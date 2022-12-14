#include "dma.h"


uint32_t SendBuff[SENDBUFF_SIZE];


static int common_nvic_config(uint32_t nvic_priority_groupx, IRQn_Type irqn, uint16_t preempt_prior_val, uint16_t sub_prior_val)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(nvic_priority_groupx);
    
    NVIC_InitStructure.NVIC_IRQChannel = irqn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preempt_prior_val;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_prior_val;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    // printf("timer NVIC config success!!!\n");
    return 0;
}

int dma_send_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, ENABLE);                      // 开启DMA时钟
    common_nvic_config(NVIC_PriorityGroup_1, irqn, 1, 1);                   // 配置DMA中断
    
    DMA_DeInit(dma_channelx);

    /*设置DMA源：内存地址＆串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = dma_addr;
    /*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = data_addr;                       // 自主设置的发送数据缓存
    /*方向：从内存到外设*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    /*传输大小*/
    DMA_InitStructure.DMA_BufferSize = data_size;
    /*外设地址不增*/  /*内存地址自增*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /*外设数据单位*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /*内存数据单位8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /*DMA模式：一次传输, 循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // DMA_Mode_Circular
    /*优先级：中*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    /*禁止内存到内存的传输*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    /*配置DMA1的4通道*/
    DMA_Init(dma_channelx, &DMA_InitStructure);
    
    DMA_Cmd(dma_channelx, ENABLE);                                          // 使能DMA
    DMA_ITConfig(dma_channelx, DMA_IT_TC, ENABLE);                          // 配置DMA发送完成后产生中断

    return 0;
}

int dma_send_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx)
{
    DMA_Cmd(dma_channelx, DISABLE);// 失能DMA

    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, DISABLE);

    DMA_DeInit(dma_channelx);

    return 0;
}

int dma_send_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, ENABLE);

    USART_DMACmd(usartx, USART_DMAReq_Tx, ENABLE);

    return 0;
}

int dma_send_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    USART_DMACmd(usartx, USART_DMAReq_Tx, DISABLE);

    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, DISABLE);

    return 0;    
}


int dma_recv_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx)
{
    //串口收DMA配置
    //启动DMA时钟
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    common_nvic_config(NVIC_PriorityGroup_1, irqn, 0, 1);                   // 配置DMA中断
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    // DMA1通道5配置
    DMA_DeInit(DMA1_Channel5);
    //外设地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
    //内存地址
    DMA_InitStructure.DMA_MemoryBaseAddr = data_addr;
    // dma传输方向单向
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    //设置DMA在传输时缓冲区的长度
    DMA_InitStructure.DMA_BufferSize = data_size;
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

    // //采用DMA方式发送
    // USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    //采用DMA方式接收
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
}

int dma_recv_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx)
{

}

int dma_recv_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{

}

int dma_recv_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    
}


//串口1接收中断   
// void USART1_IRQHandler(void)                               
// {   
//     uint32_t temp = 0;
//     uint16_t i = 0;
    
//     if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
//         //USART_ClearFlag(USART1,USART_IT_IDLE);
//         temp = USART1->SR;
//         temp = USART1->DR;                          //清USART_IT_IDLE标志
//         DMA_Cmd(DMA1_Channel5, DISABLE);
 
//         temp = UART_RX_LEN - DMA_GetCurrDataCounter(DMA1_Channel5);
//         for (i = 0;i < temp; i++) {
//             Data_Receive_Usart = Uart_Rx[i];
//               //启动串口状态机
//             usart_state_run(); 
//         }
 
//         //设置传输数据长度
//         DMA_SetCurrDataCounter(DMA1_Channel5, UART_RX_LEN);
//         //打开DMA
//         DMA_Cmd(DMA1_Channel5, ENABLE);
//     } 
    
//     // __nop(); 
// }

static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /*Configure one bit for preemption priority*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    
    /*配置P[A|B|C|D|E]0为中断源*/
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);   //开启DMA时钟
    NVIC_Config();                                       //配置DMA中断
    
    /*设置DMA源：内存地址＆串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
    
    /*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;// 自主设置的发送数据缓存
    
    /*方向：从内存到外设*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    
    /*传输大小*/
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    
    /*外设地址不增*/  /*内存地址自增*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    
    /*外设数据单位*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    
    /*内存数据单位8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    
    /*DMA模式：一次传输, 循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // DMA_Mode_Circular
    
    /*优先级：中*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    
    /*禁止内存到内存的传输*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    
    /*配置DMA1的4通道*/
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    
    DMA_Cmd(DMA1_Channel4, ENABLE);//使能DMA
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE); //配置DMA发送完成后产生中断
}


