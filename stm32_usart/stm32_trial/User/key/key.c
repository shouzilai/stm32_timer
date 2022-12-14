#include "key.h"


static volatile KEY_TYPE key_action_flag, key_last_action;    // 按键有效标志，0： 按键值无效； 1：按键值有效


static int key_gpio_config(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, GPIOMode_TypeDef gpio_mode, 
        GPIO_TypeDef *gpiox)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(rcc_apb2_periph_gpiox, ENABLE); // 开启按键端口PA的时钟
    GPIO_InitStructure.GPIO_Pin = gpio_pinx;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = gpio_mode;
    
    GPIO_Init(gpiox, &GPIO_InitStructure);

    return 0;
}

int key_config_init(uint32_t rcc_apb2_periph_gpiox, uint16_t gpio_pinx, GPIOMode_TypeDef gpio_mode, 
        GPIO_TypeDef *gpiox)
{
    key_gpio_config(rcc_apb2_periph_gpiox, gpio_pinx, gpio_mode, 
             gpiox);

    timer_init(TIM3_IRQn, 0, 0, TIM3, RCC_APB1_TIM3);

    return 0;
}

int key_config_deinit(void)
{
    timer_deinit();

    return 0;
}

int key_scan_start(void)
{
    timer_start(TIM3, RCC_APB1_TIM3);

    return 0;
}

int key_sacn_stop(void)
{
    timer_stop(TIM3, RCC_APB1_TIM3);

    return 0;
}

KEY_TYPE key_scan_return()
{
    if (key_action_flag != key_last_action) {
        key_last_action = key_action_flag;
        key_action_flag = NULL_KEY;
        return key_last_action;
    } else {
        return NULL_KEY;
    }
}

/**
 * 单个按键检测短按和长按事件
 * 短按：时间 10ms < T < 1 s, 长按：时间 T >1 s
 * 功能：使用状态机方式，扫描单个按键；扫描周期为10ms, 10ms刚好跳过抖动；
 * 状态机使用switch case语句实现状态之间的跳转
 * lock变量用于判断是否是第一次进行按键确认状态
 * --长按键事件提前执行，短按键事件释放后才执行
 */
static void key_sacn(void)
{
    static u8 TimeCnt = 0;
    static u8 lock = 0;
    static KEY_STATE KeyState;
    
    switch (KeyState)
    {
        //按键未按下状态，此时判断Key的值
        case KEY_CHECK:
            if (Key == 0) {
                KeyState =  KEY_COMFIRM;                    //如果按键Key值为0，说明按键开始按下，进入下一个状态 
            }
            TimeCnt = 0;                                    //计数复位
            lock = 0;
            break;
            
        case KEY_COMFIRM:
            if (Key == 0) {                                 //查看当前Key是否还是0，再次确认是否按下
                if (lock == 0) {
                    lock = 1;
                }   
                TimeCnt++;
                /*按键时长判断*/ 
                if (TimeCnt > 120) {
                    key_action_flag = LONG_KEY;
                    TimeCnt = 0;  
                    lock = 0;                               //重新检查
                    KeyState =  KEY_RELEASE;                // 需要进入按键释放状态
                }
            } else {
                if (lock == 1) {                            // 不是第一次进入，  释放按键才执行
                    key_action_flag = SHORT_KEY;            // 短按
                    KeyState =  KEY_RELEASE;                // 需要进入按键释放状态 
                }
                else {                                      // 当前Key值为1，确认为抖动，则返回上一个状态
                    KeyState =  KEY_CHECK;                  // 返回上一个状态
                }
            } 
            break;
            
        case KEY_RELEASE:
            if (Key == 1) {                                 //当前Key值为1，说明按键已经释放，返回开始状态
                KeyState =  KEY_CHECK;    
            }
            break;
            
        default: 
            break;
    }
}

void TIM3_IRQHandler(void)
{   
    static u8 cnt = 0, first_trial = 1;                     //TIM3 每 2ms 中断一次

    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {    //检查指定的TIM中断发生与否:TIM 中断源 
        cnt++;
        if(cnt > 5) {                                       // 每10ms 执行一次按键扫描程序
            key_last_action = key_action_flag;
            key_sacn();
            cnt = 0;
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);         //清除TIMx的中断待处理位:TIM 中断源 
    }
    if (first_trial != 0) {
        printf("key exti running...\n");
        first_trial = 0;
    }
}

// 弃用
static u8 Key_Scan(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    /*检测是否有按键按下*/
    if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
        /*延时消抖*/
        Delay(10000);
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {
            /*等待按键释放*/
            while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON) {

            }
            return KEY_ON;
        }
        else {
            return KEY_OFF;
        }
    } else {
        return KEY_OFF;
    }
}