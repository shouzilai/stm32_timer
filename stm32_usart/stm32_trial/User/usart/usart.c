#include "usart.h"


static usart_p s_usart = NULL;
static void* message_pointer = NULL;
static uint8_t usart_send_buff[USART_SEND_BUFFER_SIZE] = {0};
static uint8_t usart_recive_buff[USART_RECV_BUFFER_SIZE] = {0};

static void hup_frame_printf(hup_protocol_type_p hup_p)
{
    uint8_t* tep = (uint8_t*)hup_p;
    printf("\r\nhup frame data is ");
    for (int i = 0; i < 3; i++) {
        printf("0x%x ", *tep++);
    }
    printf("%d ", hup_p->data_len);
    tep = hup_p->data_addr;
    for (int i = 0; i < hup_p->data_len; i++) {
        printf("0x%x ", *tep++);
    }
    printf("0x%x ", hup_p->xor8);
    printf("\r\n");
}

void Delay(__IO u32 nCount)// 简单的延时函数
{
    for ( ;nCount != 0; nCount--);
}

static int common_nvic_config(uint32_t nvic_priority_groupx, IRQn_Type irqn, uint16_t preempt_prior_val, uint16_t sub_prior_val);
static int dma_send_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx);
static int dma_send_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx);
static int dma_send_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx, int data_len);
static int dma_send_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx);


static int dma_recv_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx);
static int dma_recv_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx);
static int dma_recv_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx);
static int dma_recv_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx);
/* 
首先调用函数USART1_Config(),函数USART1_Config()主要完成如下工作;
    1)使能串口1的时钟。
    2)配置usart1的I/O。
    3)配置usart1的工作模式,具体为波特率为115200、8个数据位、1个停止位、无硬件流控制。 
*/
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /*config USART1 clock (使能时钟) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /*USART1 GPIO config*/
    /*Configure USART1 Tx(PA.09)as alternate function pushpull (接收端口 为 上拉输出模式) */ 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*Configure USART1 Rx(PA.10)as input floating (接收端口 为 浮动输入模式) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*USART1 mode config (波特率为115200, 数据位为8, 停止位为1, 奇偶校验位为无, 无硬件控制流, 串口模式为RX | TX */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

static void hup_success_handle(hup_protocol_type_p hup_p)
{
    uint8_t* meg_p = (uint8_t*)message_pointer;
    meg_p[0] = hup_p->cmd;
    memcpy(&meg_p[1], hup_p->data_addr, hup_p->data_len);
    printf("hup handle is successful!!!\r\n");
}

static int usart2_info_config(usart_p usart)
{
    usart->gpiox = GPIOB;

    usart->rcc_apb2periph[0] = RCC_APB2Periph_GPIOB;
    usart->rcc_apb2periph[1] = RCC_APB1Periph_USART2;

    usart->rcc_enable[0] = ENABLE;
    usart->rcc_enable[1] = ENABLE;

    usart->tx_pin = GPIO_Pin_2;
    usart->rx_pin = GPIO_Pin_3;

    usart->usartx = USART2;

    return 0;
}

static int usart1_info_config(usart_p usart)
{
    usart->gpiox = GPIOA;

    usart->rcc_apb2periph[0] = RCC_APB2Periph_GPIOA;
    usart->rcc_apb2periph[1] = RCC_APB2Periph_USART1;

    
    usart->rcc_enable[0] = ENABLE;
    usart->rcc_enable[1] = ENABLE;

    usart->tx_pin = GPIO_Pin_9;
    usart->rx_pin = GPIO_Pin_10;

    usart->usartx = USART1;

    return 0;
}

static int usartx_config_sort(usart_p usart, USART_TypeDef* usartx)
{
    usart1_info_config(usart);
    if (usartx == USART1) {
        usart1_info_config(usart);
    } else if (usartx == USART2) {
        usart2_info_config(usart);
    } else {
        return -1;
    }
    return 0;
}

static int usart_gpio_config(usart_p usart)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*config USART1 clock (使能时钟) */
    RCC_APB2PeriphClockCmd(usart->rcc_apb2periph[0] | usart->rcc_apb2periph[1], usart->rcc_enable[0]);

    /*USART1 GPIO config*/
    /*Configure USART1 Tx(PA.09)as alternate function pushpull (接收端口 为 上拉输出模式) */ 
    GPIO_InitStructure.GPIO_Pin = usart->tx_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(usart->gpiox, &GPIO_InitStructure);
    
    /*Configure USART1 Rx(PA.10)as input floating (接收端口 为 浮动输入模式) */
    GPIO_InitStructure.GPIO_Pin = usart->rx_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(usart->gpiox, &GPIO_InitStructure);

    return 0;
}

static int usart_mode_config(usart_p usart)
{
    USART_InitTypeDef USART_InitStructure;
    
    /*USART1 mode config (波特率为115200, 数据位为8, 停止位为1, 奇偶校验位为无, 无硬件控制流, 串口模式为RX | TX */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(usart->usartx, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    return 0;
}

int usartx_init(usart_p usart, USART_TypeDef* usartx, void* message_ptr)
{
    // 1.具体串口序号初始化
    usartx_config_sort(usart, usartx);
    usart_gpio_config(usart);
    usart_mode_config(usart);

    // 2.串口工具初始化
    buffer_fifo_init(&usart->r_fifo, USART_FIFO_SIZE);
    buffer_fifo_init(&usart->w_fifo, USART_FIFO_SIZE);

    hup_init(&usart->hup_frame, USART_HUP_SIZE, hup_success_handle);

    dma_send_init(RCC_AHBPeriph_DMA1, DMA1_Channel4_IRQn, USART1_DR_Base, (u32)usart_send_buff, 
            USART_SEND_BUFFER_SIZE, DMA1_Channel4);
    dma_recv_init(RCC_AHBPeriph_DMA1, USART1_IRQn, (u32)(&USART1->DR), (u32)usart_recive_buff, 
            USART_RECV_BUFFER_SIZE, DMA1_Channel5); // (u32)(&USART1->DR)

    timer_init(TIM4_IRQn, 1, 1, TIM4, RCC_APB1_TIM4);

    // 3.led驱动的初始化 | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA
    led_config_init(RCC_APB2Periph_GPIOC, GPIOC_LED_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIOC);

    // 4.串口模块时钟停止运行，等待使用
    RCC_APB2PeriphClockCmd(usart->rcc_apb2periph[0] | usart->rcc_apb2periph[1], DISABLE);

    message_pointer = message_ptr;
    s_usart = usart;

    return 0;
}

int usartx_deinit(usart_p usart)
{
    buffer_fifo_deinit(&usart->r_fifo);
    buffer_fifo_deinit(&usart->w_fifo);

    hup_deinit(&usart->hup_frame);

    dma_send_deinit(RCC_AHBPeriph_DMA1, DMA1_Channel4);
    dma_recv_deinit(RCC_AHBPeriph_DMA1, DMA1_Channel5);

    timer_deinit();
    return 0;
}

int usartx_start(usart_p usart)
{
    RCC_APB2PeriphClockCmd(usart->rcc_apb2periph[0] | usart->rcc_apb2periph[1], usart->rcc_enable[1]);
    USART_Cmd(usart->usartx, ENABLE);

    // dma_send_start(RCC_AHBPeriph_DMA1, usart->usartx, 136);
    dma_recv_start(RCC_AHBPeriph_DMA1, usart->usartx);

    timer_start(TIM4, RCC_APB1_TIM4);
    
    return 0;
}

int usartx_stop(usart_p usart)
{
    RCC_APB2PeriphClockCmd(usart->rcc_apb2periph[0] | usart->rcc_apb2periph[1], DISABLE);
    USART_Cmd(usart->usartx, DISABLE);

    dma_send_stop(RCC_AHBPeriph_DMA1, usart->usartx);
    dma_recv_stop(RCC_AHBPeriph_DMA1, usart->usartx);

    timer_stop(TIM4, RCC_APB1_TIM4);

    return 0;
}

static int usartx_write(USART_TypeDef* usartx, uint8_t* addr, int len)
{
    assert_param(IS_USART_ALL_PERIPH(usartx));
    if (NULL == addr || len < 0 || len > 256) {
        return -1;
    }

    for (int i = 0; i < len; i++) {
        USART_SendData(usartx, *addr++);
        while (USART_GetFlagStatus(usartx, USART_FLAG_TXE) == RESET) {
        }
    }
    return 0;
}

int usart_send(usart_p usart, hup_protocol_type_em sort, int cmd, uint8_t* addr, int addr_len)
{
    if (NULL == usart) {
        printf("usart send usart is NULL!!!\n");
        return -1;
    }
    if (addr_len < 0 || NULL == addr) {
        printf("usart send addr_len or addr illegal!!!\n");
        return -1;
    }
    uint32_t temp_reg = 0;
    int frame_len = -1, frame_real_len;
    uint8_t frame[USART_SEND_BUFFER_SIZE];
    
    // 1.根据函数参数，封装hup包
    hup_protocol_type_p hup = hup_pack(sort, cmd, addr_len, addr);
    // hup_frame_printf(hup);
    frame_len = hup->data_len + 5 + 1;
    frame_real_len = frame_len - 1;

    memset(frame, 0x0, sizeof(frame));
    memcpy(&frame[1], (uint8_t*)hup, 4);          
    memcpy(&frame[5], hup->data_addr, hup->data_len);
    frame[frame_real_len] = hup->xor8;
    
    // 2.发送到串口，usart_write()
    // dma_send_stop(RCC_AHBPeriph_DMA1, usart->usartx);  // 此句话至关重要，保证了数据的有序发送，位置只能在处理send_buff前，不然大乱。
    memset(usart_send_buff, 0x0, sizeof(usart_send_buff));

    // uint8_t* data = usart_send_buff;
    buffer_fifo_write(&usart->w_fifo, &frame[1], frame_real_len);
    // for (int i = 0; i < s_usart->hup_frame.data_len + 5; i++) {
    //     int ret = buffer_fifo_read(&s_usart->w_fifo, data++, 1);
    //     if (ret != -1) {
    //         // printf("0x-%x ", usart_send_buff[i]);
    //     }
    // }
    // dma_send_start(RCC_AHBPeriph_DMA1, usart->usartx, frame_real_len);

    // for (int i = 1; i < frame_len; i++) {
    //     printf("%x ", usart_send_buff[i]);
    // }
    return 0;
}



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

int dma_send_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx, int data_len)
{
    // uint8_t temp;
    // temp = USART1->SR;
    // temp = USART1->DR;
    // USART_GetFlagStatus(usartx, USART_FLAG_TC);
    // USART_ClearFlag(usartx, USART_FLAG_TC);

    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, ENABLE);
    DMA1_Channel4->CNDTR = data_len;
    DMA_Cmd(DMA1_Channel4, ENABLE);
    USART_DMACmd(usartx, USART_DMAReq_Tx, ENABLE);
    return 0;
}

int dma_send_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    USART_DMACmd(usartx, USART_DMAReq_Tx, DISABLE);
    DMA_Cmd(DMA1_Channel4, DISABLE);
    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, DISABLE);

    return 0;    
}


int dma_recv_init(uint32_t rcc_apbperiph_dmax, IRQn_Type irqn, uint32_t dma_addr, 
        uint32_t data_addr, uint32_t data_size, DMA_Channel_TypeDef* dma_channelx)
{
    //串口收DMA配置
    //启动DMA时钟
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    common_nvic_config(NVIC_PriorityGroup_1, irqn, 0, 1);                   // 配置DMA中断
    // DMA1通道5配置
    DMA_DeInit(dma_channelx);
    //外设地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = dma_addr;
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
    DMA_Init(dma_channelx, &DMA_InitStructure);

    //使能通道5
    DMA_Cmd(dma_channelx, ENABLE);

    //中断配置
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    // USART_ITConfig(USART1, USART_IT_TC, DISABLE);
    // USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

    //配置UART1中断

    // //采用DMA方式发送
    // USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    //采用DMA方式接收
    // USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    return 0;
}

int dma_recv_deinit(uint32_t rcc_apbperiph_dmax, DMA_Channel_TypeDef* dma_channelx)
{
    DMA_Cmd(dma_channelx, DISABLE);// 失能DMA

    RCC_AHBPeriphClockCmd(rcc_apbperiph_dmax, DISABLE);

    DMA_DeInit(dma_channelx);

    return 0;
}

int dma_recv_start(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    USART_DMACmd(s_usart->usartx, USART_DMAReq_Rx, ENABLE);

    return 0;
}

int dma_recv_stop(uint32_t rcc_apbperiph_dmax, USART_TypeDef* usartx)
{
    USART_DMACmd(s_usart->usartx, USART_DMAReq_Rx, DISABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, DISABLE);

    return 0;
}


//串口1接收中断   
void USART1_IRQHandler(void)
{   
    uint8_t data = 0;
    uint32_t temp = 0;
    USART_TypeDef* usart_x = s_usart->usartx;
    
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
        // USART_ClearFlag(USART1,USART_IT_IDLE);
        
        temp = usart_x->SR;
        temp = usart_x->DR;                          //清USART_IT_IDLE标志
        DMA_Cmd(DMA1_Channel5, DISABLE);
 
        temp = USART_RECV_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);
        for (int i = 0; i < temp; i++) {
            buffer_fifo_write(&s_usart->r_fifo, (uint8_t*)&usart_recive_buff[i], 1);
            // printf("0x%x ", usart_recive_buff[i]);
        }
        // for (int i = 0;i < temp; i++) {
        //     buffer_fifo_read(&s_usart->r_fifo, &data, 1);
        //     printf("0x%x %d  ", data, temp);
        //     // hup_parse(&s_usart->hup_frame, data);
        // }
        //设置传输数据长度
        DMA_SetCurrDataCounter(DMA1_Channel5, USART_RECV_BUFFER_SIZE);
        //打开DMA
        DMA_Cmd(DMA1_Channel5, ENABLE);
    }
    memset(usart_recive_buff, 0x0, sizeof(usart_recive_buff)); 
    
}

// void USART1_IRQHandler(void)
// {   
//     uint16_t i = 0;
//     u8 data = 0;
//     uint32_t temp = 0;
//     USART_TypeDef* usart_x = s_usart->usartx;
    
//     if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
//         // USART_ClearFlag(USART1,USART_IT_IDLE);
        
//         temp = usart_x->SR;
//         temp = usart_x->DR;                          //清USART_IT_IDLE标志
//         DMA_Cmd(DMA1_Channel5, DISABLE);
 
//         temp = USART_RECV_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);
//         for (i = 0;i < temp; i++) {
//             buffer_fifo_write(&s_usart->r_fifo, (uint8_t*)&usart_recive_buff[i], temp);
//             // printf("0x%x %d  ", usart_recive_buff[i], temp);
//         }
//         for (i = 0;i < temp; i++) {
//             buffer_fifo_read(&s_usart->r_fifo, &data, 1);
//             // printf("0x%x %d  ", usart_recive_buff[i], temp);
//             hup_parse(&s_usart->hup_frame, data);
//         }
        
//         //设置传输数据长度
//         DMA_SetCurrDataCounter(DMA1_Channel5, USART_RECV_BUFFER_SIZE);
//         //打开DMA
//         DMA_Cmd(DMA1_Channel5, ENABLE);
//     }
//     // memset(usart_recive_buff, 0x0, sizeof(usart_recive_buff)); 
    
//     // __nop(); 
// }

void DMA1_Channel4_IRQHandler(void)
{
    int ret = -1;
    uint8_t *data = usart_send_buff;
    //判断是否为DMA发送完成中断
    if(DMA_GetFlagStatus(DMA1_FLAG_TC4) == SET)
    {
        // printf("trigger success\n");
        // for (int i = 0; i < s_usart->hup_frame.data_len + 5; i++) {
        //     ret = buffer_fifo_read(&s_usart->w_fifo, data, 1);
        //     if (ret != -1) {
        //         printf("0x-%x \r\n", *data);
        //     }
        // }
        // ret = buffer_fifo_read(&s_usart->w_fifo, data, s_usart->hup_frame.data_len + 5);
        // printf("0x%x\r\n", *data);
        // dma_send_start(RCC_AHBPeriph_DMA1, s_usart->usartx);
        DMA_ClearFlag(DMA1_FLAG_TC4);
    }
    // dma_send_stop(RCC_AHBPeriph_DMA1, s_usart->usartx);
}

void TIM4_IRQHandler(void)
{
    int ret = -1;
    static int count = 0;
    uint8_t r_data = 0;
    uint8_t* w_data = (uint8_t*)usart_send_buff;

    // 1.读取 w_fifo 发数据到串口设备
    // dma_send_stop(RCC_AHBPeriph_DMA1, s_usart->usartx);  // 此句话至关重要，保证了数据的有序发送，位置只能在处理send_buff前，不然大乱。
    memset(usart_send_buff, 0x0, sizeof(usart_send_buff));
    for (int i = 0; i < s_usart->hup_frame.data_len + 5; i++) {
        int ret = buffer_fifo_read(&s_usart->w_fifo, w_data++, 1);
        if (ret != -1) {
            count++;
            printf("0x-%x ", usart_send_buff[i]);  // 此链路，已通
            // printf("-%x-", *(w_data - 1));
        }
    }
    if (count > 0) {
        dma_send_start(RCC_AHBPeriph_DMA1, s_usart->usartx, s_usart->hup_frame.data_len + 5);
        printf("dma send start \n");
        count = 0;
    }

    // 2.读取 r_fifo 做出hup解析
    for (int i = 0; i < 13; i++) {
        ret = buffer_fifo_read(&s_usart->r_fifo, &r_data, 1);
        if (ret != -1) {
            // printf("0x%x ", r_data);
            hup_parse(&s_usart->hup_frame, r_data);
        }
    }
    // for (int i = 0; i < 136; i++) {
    //     ret = buffer_fifo_read(&s_usart->r_fifo, &r_data, 1);
    //     if (ret != -1) {
    //         printf("0x%x %d  ", r_data, 136);
    //         // hup_parse(&s_usart->hup_frame, data);
    //     }
    // }
}

void UART1SendByte(unsigned char SendData)
{	   
    USART_SendData(USART1, SendData);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {

    }
}

/*接收一个字节数据*/
unsigned char UART1GetByte(unsigned char* GetData)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) {  
        return 0;   //没有收到数据 
    }
    *GetData = USART_ReceiveData(USART1);
    return 1;       //收到数据
}
/*接收一个数据，马上接收到的这个数据返回给来源*/
void UART1Test(void)
{
    unsigned char i = 0;

    while (1) {    
        while (UART1GetByte(&i)) {
            USART_SendData(USART1, i);
        }
    }
}


int fputc(int ch, FILE *f)
{
    /*将Printf内容发往串口*/
    USART_SendData(USART1, (unsigned char)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return(ch);
}




/*
*函数名：USART1_printf
*描述：格式化输出,类似于C库中的printf,但这里没有用到C库
*输入：-USARTx串口通道,这里只用到了串口1,即USART1
*-Data要发送到串口的内容的指针
*-……其他参数
*输出：无
*返回：无
*调用：外部调用
*典型应用USART1_printf(USART1,"\r\n this is a demo\r\n");
*USART1_printf(USART1,"\r\n%d\r\n",i);
*USART1_printf(USART1,"\r\n%s\r\n",j);
*/
// void USART1_printf(USART_TypeDef* USARTx, uint8_t* Data, ……)
// {
//     const char*s;
//     int d;
//     char buf[16];
//     va_list ap;
//     va_start(ap, Data);
//     while (*Data != 0) { //判断是否到达字符串结束符
//         if(*Data == 0x5c)//'\'
//         {
//             switch(*++Data)
//             {
//                 case'r'://回车符
//                 USART_SendData(USARTx,0x0d);
//                 Data++;
//                 break;
            
//                 case'n'://换行符
//                 USART_SendData(USARTx,0x0a);
//                 Data++;
//                 break;
            
//                 default:
//                 Data++;
//                 break;
//             }
//         }
//         else if(*Data == '%')
//         {//
//             switch(*++Data)
//             {
//                 case's'://字符串
//                     s = va_arg(ap, const char*);
//                     for (; *s; s++) {
//                         USART_SendData(USARTx, *s);
//                         while (USART_GetFlagStatus(USARTx, USART_FLAG_TC)== RESET) {

//                         }
//                     }
//                     Data++;
//                     break;
            
//                 case'd'://十进制
//                     d=va_arg(ap, int);
//                     itoa(d, buf, 10);
//                     for (s = buf; *s ;s++) {
//                         USART_SendData(USARTx, *s);
//                         while (USART_GetFlagStatus(USARTx, USART_FLAG_TC)== RESET) {

//                         }
//                     }
//                     Data++;
//                     break;

//                 default:
//                     Data++;
//                     break;
//             }
//         }/*end of else if*/
//         else {
//             USART_SendData(USARTx, *Data++);
//         }
//         while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET) {

//         }
//     }
// }

// /*
// *函数名：itoa
// *描述：将整型数据转换成字符串
// *输入：-radix=10表示十进制,其他结果为0
// *-value要转换的整型数
// *-buf转换后的字符串
// *-radix=10
// *输出：无
// *返回：无
// *调用：被USART1_printf()调用
// */
// static char* itoa(int value, char* string, int radix)
// {
//     int i, d;
//     int flag = 0;
//     char* ptr = string;
    
//     /*This implementation only works for decimal numbers.*/
//     if (radix != 10) {
//         *ptr = 0;
//         return string;
//     }
    
//     if (!value) {
//         *ptr ++= 0x30;
//         *ptr = 0;
//         return string;
//     }
    
//     /*if this is a negative value insert the minus sign.*/
//     if (value < 0) {
//         *ptr ++= '-';
//         /*Make the value positive.*/
//         value *= -1;
//     }
//     for (i = 10000; i > 0; i /= 10) {
//         d = value / i;
//         if (d || flag) {
//             *ptr ++= (char)(d + 0x30);
//             value -= (d * i);
//             flag = 1;
//         }
//     }
    
//     /*Null terminate the string.*/
//     *ptr = 0;

//     return string;
// }/*NCL_Itoa*/