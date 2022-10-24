#line 1 "D:\\stm32_trial\\FWlib\\src\\stm32f10x_dma.c"



















 

 
#line 1 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"




















 

 







 
#line 1 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







































 



 



 
    






  


 
  


 
   
#line 75 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"


















 





#line 107 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







        

   
#line 124 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"





 






 
#line 145 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 



 



 
#line 164 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 223 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 244 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_IRQn               = 24,      
  TIM1_UP_IRQn                = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42         


#line 298 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 343 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 383 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 428 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 474 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "D:\\stm32_trial\\CMSIS\\core_cm3.h"
 




 

























 



 #pragma system_include          







#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\stdint.h"
 
 




  #pragma system_include


#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include















 





#line 11 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\stdint.h"
#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"
 
 





  #pragma system_include


 









  


 


 




 
#pragma rtmodel = "__dlib_version", "6"

 





 
#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"



























 





  #pragma system_include


 
#line 1 "C:\\\\Program Files (x86)\\\\IAR Systems\\\\Embedded Workbench 8.0\\\\arm\\\\INC\\\\c\\\\DLib_Config_Full.h"
 
 





  #pragma system_include


 


 


 


 


#line 40 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"
   
#line 47 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"

 
#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Product.h"
 





   #pragma system_include







 




 



 



 



 


 









 


 


 






 




 




 


 


 


 
#line 106 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Product.h"









#line 51 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"











 



















 














 


























 








 






 

#line 153 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"









 

#line 172 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"













 
















 








 
#line 223 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"













 
















 





















 














 








 
#line 311 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"








 
#line 331 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"






 








 















 








 
















 




#line 400 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"





 

#line 414 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"


   
#line 424 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"

#line 432 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"

  







 









 









 







 







 
















 


   
#line 504 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"




 










 

#line 528 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"






 










 













 

#line 568 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\DLib_Defaults.h"



 












#line 43 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"



















 

#line 83 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

 







 
#line 102 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"














 


   
#line 128 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"





 
#line 141 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"










 
#line 196 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

#line 204 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

#line 211 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

 


 




 
#line 232 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"
  typedef unsigned int _Wchart;

    typedef unsigned int _Wintt;
#line 255 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

 


 
typedef unsigned int     _Sizet;

 
typedef struct _Mbstatet
{  

    unsigned int _Wchar;   
    unsigned int _State;   
#line 275 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

#line 299 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"
} _Mbstatet;






 


 





  typedef struct __va_list
  {
    char  *_Ap;
  } __va_list;
  typedef __va_list __Va_list;












    typedef struct __FILE _Filet;



 
typedef struct
{       

    long long _Off;     



  _Mbstatet _Wstate;
} _Fpost;





 


 

  
    
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_StaticGuard(void);



      _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockfilelock(_Filet *);
      _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockfilelock(_Filet *);



  typedef void *__iar_Rmtx;

  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Initdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Dstdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockdynamiclock(__iar_Rmtx *);

  
#line 406 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"

#line 446 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\yvals.h"






 
#line 12 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\stdint.h"





 

  typedef signed char          int8_t;
  typedef unsigned char        uint8_t;



  typedef signed short int         int16_t;
  typedef unsigned short int       uint16_t;



  typedef signed int         int32_t;
  typedef unsigned int       uint32_t;



  typedef signed long long int         int64_t;
  typedef unsigned long long int       uint64_t;



 
typedef signed char      int_least8_t;
typedef unsigned char    uint_least8_t;

typedef signed short int     int_least16_t;
typedef unsigned short int   uint_least16_t;

typedef signed int     int_least32_t;
typedef unsigned int   uint_least32_t;

 

  typedef signed long long int   int_least64_t;


  typedef unsigned long long int uint_least64_t;




 
typedef signed int       int_fast8_t;
typedef unsigned int     uint_fast8_t;

typedef signed int      int_fast16_t;
typedef unsigned int    uint_fast16_t;

typedef signed int      int_fast32_t;
typedef unsigned int    uint_fast32_t;


  typedef signed long long int    int_fast64_t;


  typedef unsigned long long int  uint_fast64_t;


 
typedef signed long long int          intmax_t;
typedef unsigned long long int        uintmax_t;


 
typedef signed int          intptr_t;
typedef unsigned int        uintptr_t;

 



typedef int __data_intptr_t; typedef unsigned int __data_uintptr_t;


 

























































































 



































 
#line 45 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

















 




 



 

 








#line 101 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

#line 120 "D:\\stm32_trial\\CMSIS\\core_cm3.h"



 


#line 145 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

#line 162 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

#line 1 "D:\\stm32_trial\\CMSIS\\core_cmInstr.h"
 




 

























 



 #pragma system_include          








 



 

 
#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"
















 
 











#pragma message("\nWarning: The header file 'cmsis_iar.h' is obsolete and should not be used.")
#pragma message("         A sutiable version is automatically included from the CMSIS-core package.")
#pragma message("         This file will be removed in a future release.")

#pragma system_include








 
#line 63 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"
 
 
#line 72 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"
 


































  #pragma language=save
  #pragma language=extended
  _Pragma("inline=forced") __intrinsic uint16_t __iar_uint16_read(void const *ptr) {
    return *(__packed uint16_t*)(ptr);
  }
  #pragma language=restore





  #pragma language=save
  #pragma language=extended
  _Pragma("inline=forced") __intrinsic void __iar_uint16_write(void const *ptr, uint16_t val) {
    *(__packed uint16_t*)(ptr) = val;;
  }
  #pragma language=restore




  #pragma language=save
  #pragma language=extended
  _Pragma("inline=forced") __intrinsic uint32_t __iar_uint32_read(void const *ptr) {
    return *(__packed uint32_t*)(ptr);
  }
  #pragma language=restore




  #pragma language=save
  #pragma language=extended
  _Pragma("inline=forced") __intrinsic void __iar_uint32_write(void const *ptr, uint32_t val) {
    *(__packed uint32_t*)(ptr) = val;;
  }
  #pragma language=restore




  #pragma language=save
  #pragma language=extended
  __packed struct  __iar_u32 { uint32_t v; };
  #pragma language=restore












#line 179 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"

#line 1 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\iccarm_builtin.h"








 







  #pragma system_include




 





 









#pragma language=save
#pragma language=extended

__intrinsic __nounwind void    __iar_builtin_no_operation(void);

__intrinsic __nounwind void    __iar_builtin_disable_interrupt(void);
__intrinsic __nounwind void    __iar_builtin_enable_interrupt(void);

typedef unsigned int __istate_t;

__intrinsic __nounwind __istate_t __iar_builtin_get_interrupt_state(void);
__intrinsic __nounwind void __iar_builtin_set_interrupt_state(__istate_t);

 
__intrinsic __nounwind unsigned int __iar_builtin_get_PSR( void );
__intrinsic __nounwind unsigned int __iar_builtin_get_IPSR( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_MSP( void );
__intrinsic __nounwind void         __iar_builtin_set_MSP( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_PSP( void );
__intrinsic __nounwind void         __iar_builtin_set_PSP( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_PRIMASK( void );
__intrinsic __nounwind void         __iar_builtin_set_PRIMASK( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_CONTROL( void );
__intrinsic __nounwind void         __iar_builtin_set_CONTROL( unsigned int );

 
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_FAULTMASK( void );
__intrinsic __nounwind void         __iar_builtin_set_FAULTMASK(unsigned int);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_BASEPRI( void );
__intrinsic __nounwind void         __iar_builtin_set_BASEPRI( unsigned int );

 
__intrinsic __nounwind void __iar_builtin_disable_irq(void);
__intrinsic __nounwind void __iar_builtin_enable_irq(void);

__intrinsic __nounwind void __iar_builtin_disable_fiq(void);
__intrinsic __nounwind void __iar_builtin_enable_fiq(void);


 

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SWP( unsigned int, volatile unsigned int * );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned char __iar_builtin_SWPB( unsigned char, volatile unsigned char * );

typedef unsigned int __ul;
typedef unsigned int __iar_builtin_uint;






 

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_CDP (unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) opc1, unsigned __constrange(0,15) CRd, unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opc2) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_CDP2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) opc1, unsigned __constrange(0,15) CRd, unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opc2) ;

 
__intrinsic __nounwind void          __iar_builtin_MCR( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __iar_builtin_uint src,
                                unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 )  ;
__intrinsic __nounwind unsigned int __iar_builtin_MRC( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 )  ;
__intrinsic __nounwind void          __iar_builtin_MCR2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __iar_builtin_uint src,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 ) ;
__intrinsic __nounwind unsigned int __iar_builtin_MRC2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 ) ;

__intrinsic __nounwind void __iar_builtin_MCRR (unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned long long src, unsigned __constrange(0,15) CRm) ;
__intrinsic __nounwind void __iar_builtin_MCRR2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned long long src, unsigned __constrange(0,15) CRm) ;

__intrinsic __nounwind unsigned long long __iar_builtin_MRRC (unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned __constrange(0,15) CRm) ;
__intrinsic __nounwind unsigned long long __iar_builtin_MRRC2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned __constrange(0,15) CRm) ;

 
__intrinsic __nounwind void __iar_builtin_LDC  ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDCL ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDC2 ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;

 
__intrinsic __nounwind void __iar_builtin_STC  ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STCL ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STC2 ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;

 
__intrinsic __nounwind void __iar_builtin_LDC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                                unsigned __constrange(0,255) option);

 
__intrinsic __nounwind void __iar_builtin_STC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                                unsigned __constrange(0,255) option);



 
__intrinsic __nounwind unsigned int       __iar_builtin_rsr(__spec_string const char * special_register)   ;
__intrinsic __nounwind unsigned long long __iar_builtin_rsr64(__spec_string const char * special_register) ;
__intrinsic __nounwind void*              __iar_builtin_rsrp(__spec_string const char * special_register)  ;

 
__intrinsic __nounwind void __iar_builtin_wsr(__spec_string const char * special_register, unsigned int value)         ;
__intrinsic __nounwind void __iar_builtin_wsr64(__spec_string const char * special_register, unsigned long long value) ;
__intrinsic __nounwind void __iar_builtin_wsrp(__spec_string const char * special_register, const void *value)         ;

 
__intrinsic __nounwind unsigned int __iar_builtin_get_APSR( void );
__intrinsic __nounwind void         __iar_builtin_set_APSR( unsigned int );

 
__intrinsic __nounwind unsigned int __iar_builtin_get_CPSR( void );
__intrinsic __nounwind void         __iar_builtin_set_CPSR( unsigned int );

 
__intrinsic __nounwind unsigned int __iar_builtin_get_FPSCR( void );
__intrinsic __nounwind void __iar_builtin_set_FPSCR( unsigned int );

 
 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CLZ(unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_ROR(unsigned int, unsigned int) ;
__intrinsic __nounwind unsigned int __iar_builtin_RRX(unsigned int);

 
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QADD( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDADD( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QSUB( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDSUB( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDOUBLE( signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int         __iar_builtin_QFlag( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_reset_Q_flag( void );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int         __iar_builtin_QCFlag( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_reset_QC_flag( void );

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_SMUL( signed short, signed short );

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_REV( unsigned int );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_REVSH( short );

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_REV16( unsigned int );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_RBIT( unsigned int );

_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned char  __iar_builtin_LDREXB( volatile unsigned char const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned short __iar_builtin_LDREXH( volatile unsigned short const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_LDREX ( volatile unsigned int const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned long long __iar_builtin_LDREXD( volatile unsigned long long const * );

_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXB( unsigned char, volatile unsigned char * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXH( unsigned short, volatile unsigned short * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREX ( unsigned int, volatile unsigned int * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXD( unsigned long long, volatile unsigned long long * );

__intrinsic __nounwind void __iar_builtin_CLREX( void );

__intrinsic __nounwind void __iar_builtin_SEV( void );
__intrinsic __nounwind void __iar_builtin_WFE( void );
__intrinsic __nounwind void __iar_builtin_WFI( void );
__intrinsic __nounwind void __iar_builtin_YIELD( void );

__intrinsic __nounwind void __iar_builtin_PLI( volatile void const * );
__intrinsic __nounwind void __iar_builtin_PLD( volatile void const * );
__intrinsic __nounwind void __iar_builtin_PLDW( volatile void const * );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind   signed int   __iar_builtin_SSAT     (signed int val,
                                      unsigned int __constrange( 1, 32 ) sat );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind   unsigned int __iar_builtin_USAT     (signed int val,
                                      unsigned int __constrange( 0, 31 ) sat );

 
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SEL( unsigned int op1, unsigned int op2 );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAD8(unsigned int x, unsigned int y );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USADA8(unsigned int x, unsigned int y,
                                   unsigned int acc );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSAT16   (unsigned int pair,
                                      unsigned int __constrange( 1, 16 ) sat );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAT16   (unsigned int pair,
                                      unsigned int __constrange( 0, 15 ) sat );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUAD (unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUSD (unsigned int x, unsigned int y);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUADX(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUSDX(unsigned int x, unsigned int y);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAD (unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLSD (unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLADX(unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLSDX(unsigned int x, unsigned int y, int sum);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALD (unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALDX(unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLSLD (unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLSLDX(unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_PKHBT(unsigned int x,
                                  unsigned int y,
                                  unsigned __constrange(0,31) count);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_PKHTB(unsigned int x,
                                  unsigned int y,
                                  unsigned __constrange(0,32) count);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLABB(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLABT(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLATB(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLATT(unsigned int x, unsigned int y, int acc);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAWB(int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAWT(int x, unsigned int y, int acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLA (int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLAR(int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLS (int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLSR(int x, int y, int acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMUL (int x, int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMULR(int x, int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULBB(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULBT(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULTB(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULTT(unsigned int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULWB(int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULWT(int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SXTAB (int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SXTAH (int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAB (unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAH (unsigned int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned long long __iar_builtin_UMAAL(unsigned int x,
                                       unsigned int y,
                                       unsigned int a,
                                       unsigned int b);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALBB(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALBT(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALTB(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALTT(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTB16(unsigned int x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAB16(unsigned int acc, unsigned int x);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SXTB16(unsigned int x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SXTAB16(unsigned int acc, unsigned int x);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHASX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSAX(unsigned int, unsigned int) ;

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHASX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSAX(unsigned int, unsigned int) ;

 
__intrinsic __nounwind void __iar_builtin_DMB(void);
__intrinsic __nounwind void __iar_builtin_DSB(void);
__intrinsic __nounwind void __iar_builtin_ISB(void);

 
__intrinsic __nounwind unsigned int __iar_builtin_TT(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTT(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTA(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTAT(unsigned int);

__intrinsic __nounwind unsigned int __get_LR(void);
__intrinsic __nounwind void __set_LR(unsigned int);

__intrinsic __nounwind unsigned int __get_SP(void);
__intrinsic __nounwind void __set_SP(unsigned int);

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VSQRT_F32(float x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VSQRT_F64(double x);

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFMA_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFMS_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFNMA_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFNMS_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFMA_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFMS_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFNMA_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFNMS_F64(double x, double y, double z);

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32B(unsigned int crc, unsigned char data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32H(unsigned int crc, unsigned short data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32W(unsigned int crc, unsigned int data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CB(unsigned int crc, unsigned char data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CH(unsigned int crc, unsigned short data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CW(unsigned int crc, unsigned int data);

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VMAXNM_F32(float a, float b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VMINNM_F32(float a, float b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VMAXNM_F64(double a, double b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VMINNM_F64(double a, double b);

 
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTA_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTM_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTN_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTP_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTX_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTR_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTZ_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTA_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTM_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTN_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTP_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTX_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTR_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTZ_F64(double a);

#pragma language=restore
















#line 181 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"

#line 188 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"













#line 208 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"

#line 219 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"

#line 238 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"






  _Pragma("inline=forced") __intrinsic uint8_t __CLZ(uint32_t val) {
	return __iar_builtin_CLZ(val);
  }














_Pragma("inline=forced") __intrinsic int32_t __REVSH(int32_t val) {
  return __iar_builtin_REVSH((int16_t)val);
}









  







  



#line 349 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"
  


#line 392 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"



  _Pragma("inline=forced") __intrinsic uint8_t __LDRBT(volatile uint8_t *addr) {
    uint32_t res;
    __asm("LDRBT %0, [%1]" : "=r" (res) : "r" (addr) : "memory");
    return ((uint8_t)res);
  }

  _Pragma("inline=forced") __intrinsic uint16_t __LDRHT(volatile uint16_t *addr) {
    uint32_t res;
    __asm("LDRHT %0, [%1]" : "=r" (res) : "r" (addr) : "memory");
    return ((uint16_t)res);
  }

  _Pragma("inline=forced") __intrinsic uint32_t __LDRT(volatile uint32_t *addr) {
    uint32_t res;
    __asm("LDRT %0, [%1]" : "=r" (res) : "r" (addr) : "memory");
    return res;
  }

  _Pragma("inline=forced") __intrinsic void __STRBT(uint8_t value, volatile uint8_t *addr) {
    __asm("STRBT %1, [%0]" : : "r" (addr), "r" ((uint32_t)value) : "memory");
  }

  _Pragma("inline=forced") __intrinsic void __STRHT(uint16_t value, volatile uint16_t *addr) {
    __asm("STRHT %1, [%0]" : : "r" (addr), "r" ((uint32_t)value) : "memory");
  }

  _Pragma("inline=forced") __intrinsic void __STRT(uint32_t value, volatile uint32_t *addr) {
    __asm("STRT %1, [%0]" : : "r" (addr), "r" (value) : "memory");
  }



#line 497 "C:\\Program Files (x86)\\IAR Systems\\Embedded Workbench 8.0\\arm\\inc\\c\\cmsis_iar.h"




#pragma diag_default=Pe940
#pragma diag_default=Pe177

#line 66 "D:\\stm32_trial\\CMSIS\\core_cmInstr.h"

 
#line 84 "D:\\stm32_trial\\CMSIS\\core_cmInstr.h"

   

#line 164 "D:\\stm32_trial\\CMSIS\\core_cm3.h"
#line 1 "D:\\stm32_trial\\CMSIS\\core_cmFunc.h"
 




 

























 



 #pragma system_include          








 



 

 
#line 66 "D:\\stm32_trial\\CMSIS\\core_cmFunc.h"

 
#line 84 "D:\\stm32_trial\\CMSIS\\core_cmFunc.h"

 

#line 165 "D:\\stm32_trial\\CMSIS\\core_cm3.h"
















 
#line 203 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

 






 
#line 219 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

 




 












 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:27;               
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 


















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:15;               
    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 



























 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t _reserved1:30;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 







 



 
typedef struct
{
  volatile uint32_t ISER[8U];                
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];                
        uint32_t RSERVED1[24U];
  volatile uint32_t ISPR[8U];                
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];                
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];                
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];                
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                    
}  NVIC_Type;

 



 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
  volatile uint32_t VTOR;                    
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
  volatile uint8_t  SHP[12U];                
  volatile uint32_t SHCSR;                   
  volatile uint32_t CFSR;                    
  volatile uint32_t HFSR;                    
  volatile uint32_t DFSR;                    
  volatile uint32_t MMFAR;                   
  volatile uint32_t BFAR;                    
  volatile uint32_t AFSR;                    
  volatile const  uint32_t PFR[2U];                 
  volatile const  uint32_t DFR;                     
  volatile const  uint32_t ADR;                     
  volatile const  uint32_t MMFR[4U];                
  volatile const  uint32_t ISAR[5U];                
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                   
} SCB_Type;

 















 






























 




#line 500 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

 





















 









 


















 










































 









 









 















 







 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const  uint32_t ICTR;                    



        uint32_t RESERVED1[1U];

} SCnSCB_Type;

 



 










 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 







 



 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                  
    volatile  uint16_t   u16;                 
    volatile  uint32_t   u32;                 
  }  PORT [32U];                          
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;                     
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;                     
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;                     
        uint32_t RESERVED3[29U];
  volatile  uint32_t IWR;                     
  volatile const  uint32_t IRR;                     
  volatile uint32_t IMCR;                    
        uint32_t RESERVED4[43U];
  volatile  uint32_t LAR;                     
  volatile const  uint32_t LSR;                     
        uint32_t RESERVED5[6U];
  volatile const  uint32_t PID4;                    
  volatile const  uint32_t PID5;                    
  volatile const  uint32_t PID6;                    
  volatile const  uint32_t PID7;                    
  volatile const  uint32_t PID0;                    
  volatile const  uint32_t PID1;                    
  volatile const  uint32_t PID2;                    
  volatile const  uint32_t PID3;                    
  volatile const  uint32_t CID0;                    
  volatile const  uint32_t CID1;                    
  volatile const  uint32_t CID2;                    
  volatile const  uint32_t CID3;                    
} ITM_Type;

 



 



























 



 



 



 









   







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t CYCCNT;                  
  volatile uint32_t CPICNT;                  
  volatile uint32_t EXCCNT;                  
  volatile uint32_t SLEEPCNT;                
  volatile uint32_t LSUCNT;                  
  volatile uint32_t FOLDCNT;                 
  volatile const  uint32_t PCSR;                    
  volatile uint32_t COMP0;                   
  volatile uint32_t MASK0;                   
  volatile uint32_t FUNCTION0;               
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t FUNCTION1;               
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t FUNCTION2;               
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;                   
  volatile uint32_t MASK3;                   
  volatile uint32_t FUNCTION3;               
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   







 



 
typedef struct
{
  volatile uint32_t SSPSR;                   
  volatile uint32_t CSPSR;                   
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;                    
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;                    
        uint32_t RESERVED2[131U];
  volatile const  uint32_t FFSR;                    
  volatile uint32_t FFCR;                    
  volatile const  uint32_t FSCR;                    
        uint32_t RESERVED3[759U];
  volatile const  uint32_t TRIGGER;                 
  volatile const  uint32_t FIFO0;                   
  volatile const  uint32_t ITATBCTR2;               
        uint32_t RESERVED4[1U];
  volatile const  uint32_t ITATBCTR0;               
  volatile const  uint32_t FIFO1;                   
  volatile uint32_t ITCTRL;                  
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;                
  volatile uint32_t CLAIMCLR;                
        uint32_t RESERVED7[8U];
  volatile const  uint32_t DEVID;                   
  volatile const  uint32_t DEVTYPE;                 
} TPI_Type;

 



 



 












 






 



 





















 



 





















 



 



 


















 






   


#line 1223 "D:\\stm32_trial\\CMSIS\\core_cm3.h"







 



 
typedef struct
{
  volatile uint32_t DHCSR;                   
  volatile  uint32_t DCRSR;                   
  volatile uint32_t DCRDR;                   
  volatile uint32_t DEMCR;                   
} CoreDebug_Type;

 




































 






 







































 







 






 







 


 







 

 
#line 1372 "D:\\stm32_trial\\CMSIS\\core_cm3.h"

#line 1381 "D:\\stm32_trial\\CMSIS\\core_cm3.h"






 










 


 



 





 









 
static inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);              

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));  
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U)                      );               
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}






 
static inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}






 
static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}






 
static inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}








 
static inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)(int32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}






 
static inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}






 
static inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}








 
static inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)(int32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}








 
static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) < 0)
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)(int32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)(int32_t)IRQn)]               = (uint8_t)((priority << (8U - 4)) & (uint32_t)0xFFUL);
  }
}










 
static inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) < 0)
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)(int32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4)));
  }
  else
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)(int32_t)IRQn)]               >> (8U - 4)));
  }
}












 
static inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4)) ? (uint32_t)(4) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4)) ? (uint32_t)(4) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}





 
static inline void NVIC_SystemReset(void)
{
  __iar_builtin_DSB();                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = (uint32_t)((0x5FAUL << 16U)    |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U)    );          
  __iar_builtin_DSB();                                                           

  for(;;)                                                            
  {
    __iar_builtin_no_operation();
  }
}

 



 





 













 
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  NVIC_SetPriority (SysTick_IRQn, (1UL << 4) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 



 





 

extern volatile int32_t ITM_RxBuffer;                     










 
static inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&       
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL               ) != 0UL)   )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __iar_builtin_no_operation();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}







 
static inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5U)
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5U;        
  }

  return (ch);
}







 
static inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == 0x5AA55AA5U)
  {
    return (0);                               
  }
  else
  {
    return (1);                               
  }
}

 










#line 481 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"
#line 1 "D:\\stm32_trial\\CMSIS\\system_stm32f10x.h"



















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 482 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
#line 922 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"
} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1314 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 1337 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



#line 1356 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




















 
  


   

#line 1456 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1517 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1693 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 1700 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 








 








 






#line 1736 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 











 











 













 






#line 1852 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




#line 1872 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





#line 1885 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 1904 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 1913 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 1921 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



















#line 1946 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"












 













#line 1978 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"





#line 1992 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 1999 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2009 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"











 


















#line 2045 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2053 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



















#line 2078 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"












 













#line 2110 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"





#line 2124 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2131 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2141 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"











 








 








   
#line 2180 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2275 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2302 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2464 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2482 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2500 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2517 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2535 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2554 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 

 






 
#line 2581 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2656 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 










#line 2687 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 
#line 2702 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2711 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

   
#line 2720 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2729 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 
#line 2744 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2753 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

   
#line 2762 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2771 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 
#line 2786 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2795 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

   
#line 2804 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2813 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 
#line 2828 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2837 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

   
#line 2846 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2855 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2864 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2873 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 2883 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2947 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 2982 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3017 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3052 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3087 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3154 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 



 









 
#line 3178 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




 




 
#line 3194 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 





 
#line 3216 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 





 
#line 3231 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"
 
#line 3238 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3287 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3309 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3331 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3353 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3375 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3397 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 
 
 
 

 
#line 3433 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3463 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3473 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3497 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3521 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3545 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3569 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3593 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 
#line 3617 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3718 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3727 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"















  
 
#line 3750 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3885 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3892 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3899 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3906 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







 
#line 3920 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3927 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3934 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3941 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3948 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3955 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 3963 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3970 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3977 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3984 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3991 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 3998 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 4006 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 4013 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 4020 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 4027 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4169 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 4179 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4227 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 

























 
#line 4270 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 4284 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 4294 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4413 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4448 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"





#line 4459 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 4467 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 4474 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4496 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4558 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 
#line 4570 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4608 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 











#line 4631 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 











#line 4654 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 











#line 4677 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5074 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5083 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5092 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5103 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5113 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5123 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5133 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5144 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5154 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5164 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5174 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5185 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5195 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5205 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5215 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5226 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5236 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5246 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5256 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5267 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5277 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5287 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5297 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5308 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5318 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5328 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5338 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5349 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5359 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5369 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

#line 5379 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5427 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5497 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5512 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5538 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5759 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 5771 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 






 
#line 5788 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5932 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 5944 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 5956 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 5968 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 5980 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 5992 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6004 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6016 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 

 


#line 6030 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6042 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6054 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6066 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6078 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6090 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6102 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6114 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6126 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6138 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6150 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6162 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6174 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6186 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6198 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 


#line 6210 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6230 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6241 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6259 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"











 





 





 
#line 6297 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 












 
#line 6318 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6458 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6475 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6492 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6509 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6543 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6577 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6611 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6645 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6679 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6713 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6747 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6781 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6815 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6849 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6883 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6917 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6951 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 6985 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7019 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7053 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7087 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7121 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7155 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7189 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7223 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7257 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7291 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7325 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7359 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7393 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7427 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7461 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 
 
 
 

 









#line 7488 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7496 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7506 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7567 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7576 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







 



#line 7597 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 



 


 
#line 7622 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7632 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7658 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 



 
#line 7682 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7691 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"







 
#line 7711 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
#line 7722 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 
 
 
 
 

 


#line 7751 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 









#line 7785 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7825 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8289 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"



 

 

  

#line 1 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"



















 

 



 
 
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"




















 

 







 
#line 1 "D:\\stm32_trial\\CMSIS\\stm32f10x.h"







































 



 



 
    
#line 8329 "D:\\stm32_trial\\CMSIS\\stm32f10x.h"



 

  

 

 
#line 33 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"



 



 



 



 

typedef struct
{
  uint32_t ADC_Mode;                      

 

  FunctionalState ADC_ScanConvMode;       

 

  FunctionalState ADC_ContinuousConvMode; 

 

  uint32_t ADC_ExternalTrigConv;          

 

  uint32_t ADC_DataAlign;                 
 

  uint8_t ADC_NbrOfChannel;               

 
}ADC_InitTypeDef;


 



 










 

#line 104 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"

#line 115 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 

#line 129 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"




#line 139 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"

#line 154 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 







 



 

#line 192 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"




#line 205 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 

#line 229 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 

















#line 266 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 

#line 282 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 

#line 297 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"

#line 305 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 











 



 

#line 338 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_adc.h"


 



 





 



 





 



 





 



 





  




 




 



 





 



 





 



 



 



 



 

void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);









 



 



 

 
#line 29 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_bkp.h"




















 

 







 




 



 



 



 



 



 







 



 

#line 78 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_bkp.h"


 



 

#line 128 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_bkp.h"

#line 143 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_bkp.h"




 



 



 



 



 

void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);








 



 



 

 
#line 30 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"




















 

 







 




 



 



 






 

typedef struct
{
  uint16_t CAN_Prescaler;   
 
  
  uint8_t CAN_Mode;         

 

  uint8_t CAN_SJW;          



 

  uint8_t CAN_BS1;          

 

  uint8_t CAN_BS2;          


 
  
  FunctionalState CAN_TTCM; 

 
  
  FunctionalState CAN_ABOM;  

 

  FunctionalState CAN_AWUM;  

 

  FunctionalState CAN_NART;  

 

  FunctionalState CAN_RFLM;  

 

  FunctionalState CAN_TXFP;  

 
} CAN_InitTypeDef;



 

typedef struct
{
  uint16_t CAN_FilterIdHigh;         

 

  uint16_t CAN_FilterIdLow;          

 

  uint16_t CAN_FilterMaskIdHigh;     


 

  uint16_t CAN_FilterMaskIdLow;      


 

  uint16_t CAN_FilterFIFOAssignment; 
 
  
  uint8_t CAN_FilterNumber;           

  uint8_t CAN_FilterMode;            
 

  uint8_t CAN_FilterScale;           
 

  FunctionalState CAN_FilterActivation; 
 
} CAN_FilterInitTypeDef;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     

 

  uint8_t RTR;     

 

  uint8_t DLC;     

 

  uint8_t Data[8]; 
 
} CanTxMsg;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     

 

  uint8_t RTR;     

 

  uint8_t DLC;     
 

  uint8_t Data[8]; 
 

  uint8_t FMI;     

 
} CanRxMsg;



 



 



 






 



 












 





   










 
  



   







 



 










 



 

#line 301 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"




 



 

#line 319 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"





 



 





 



 







 



 








 



 









 



 







 



 



 



 








 



 







 



 







 



 








 



 








 



 






 



 






 




   
                                                                
#line 493 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"




 



 

 
 

 




 
#line 518 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"

 



 

 





#line 539 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"








 

  


 


  


 
#line 565 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"

 



 






 





#line 590 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"

#line 597 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"



 



 
#line 621 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_can.h"



 



 



 



 



 
  
void CAN_DeInit(CAN_TypeDef* CANx);

  
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_SlaveStartBank(uint8_t CAN_BankNumber); 
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState);

 
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);

 
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);


 
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);

 
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx);
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx);
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx);

 
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState);
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);








 



 



 

 
#line 31 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_cec.h"




















 

 







 




 



 
  



 
   


  
typedef struct
{
  uint16_t CEC_BitTimingMode; 
 
  uint16_t CEC_BitPeriodMode; 
 
}CEC_InitTypeDef;



 



  
  


  







 



  







  




  
#line 100 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_cec.h"


  




  



  



  




 



 
   


  
#line 136 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_cec.h"



  
#line 147 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_cec.h"


                               
#line 157 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_cec.h"



  



  



 
 


 



  
void CEC_DeInit(void);
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);
void CEC_Cmd(FunctionalState NewState);
void CEC_ITConfig(FunctionalState NewState);
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);
void CEC_SetPrescaler(uint16_t CEC_Prescaler);
void CEC_SendDataByte(uint8_t Data);
uint8_t CEC_ReceiveDataByte(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessageCmd(FunctionalState NewState);
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG);
void CEC_ClearFlag(uint32_t CEC_FLAG);
ITStatus CEC_GetITStatus(uint8_t CEC_IT);
void CEC_ClearITPendingBit(uint16_t CEC_IT);









  



  



  

 
#line 32 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_crc.h"




















 

 







 




 



 



 



 



 



 



 



 



 

void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);








 



 



 

 
#line 33 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"




















 

 







 




 



 



 



 

typedef struct
{
  uint32_t DAC_Trigger;                      
 

  uint32_t DAC_WaveGeneration;               

 

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; 

 

  uint32_t DAC_OutputBuffer;                 
 
}DAC_InitTypeDef;



 



 



 

#line 94 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"

#line 104 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"



 



 

#line 119 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"


 



 

#line 151 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"

#line 176 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"


 



 







 



 







 



 

#line 214 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"


 



 







 



 




 
#line 261 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"



 



 



 



 

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);



void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
#line 299 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dac.h"








 



 



 

 
#line 34 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dbgmcu.h"




















 

 







 




 



 



 



 



 

#line 80 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dbgmcu.h"
                                              



  



 



 



 

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);








 



 



 

 
#line 35 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dma.h"




















 

 
#line 427 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_dma.h"


 



 



 

 
#line 36 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_exti.h"




















 

 







 




 



 



 



 

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;





 

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;






 

typedef struct
{
  uint32_t EXTI_Line;               
 
   
  EXTIMode_TypeDef EXTI_Mode;       
 

  EXTITrigger_TypeDef EXTI_Trigger; 
 

  FunctionalState EXTI_LineCmd;     
  
}EXTI_InitTypeDef;



 



 



 

#line 124 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_exti.h"
                                          
#line 136 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_exti.h"

                    


 



 



 



 



 

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);








 



 



 

 
#line 37 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"




















 

 







 




 



 



 



 

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;



 



 



 

#line 77 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"


 



 







 



 







 



 

 
#line 118 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"

 
#line 144 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"

 
#line 211 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"











 



 







 



 







 



 





#line 270 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"


 


 
#line 291 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"






 



 
#line 333 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"





 
#line 346 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"



 



 



 



 



 

 
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

 
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);

#line 408 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_flash.h"








 



 



 

 
#line 38 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"




















 

 







 




 



 



 



 

typedef struct
{
  uint32_t FSMC_AddressSetupTime;       


 

  uint32_t FSMC_AddressHoldTime;        


 

  uint32_t FSMC_DataSetupTime;          


 

  uint32_t FSMC_BusTurnAroundDuration;  


 

  uint32_t FSMC_CLKDivision;            

 

  uint32_t FSMC_DataLatency;            





 

  uint32_t FSMC_AccessMode;             
 
}FSMC_NORSRAMTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;                
 

  uint32_t FSMC_DataAddressMux;      

 

  uint32_t FSMC_MemoryType;          

 

  uint32_t FSMC_MemoryDataWidth;     
 

  uint32_t FSMC_BurstAccessMode;     

 
                                       
  uint32_t FSMC_AsynchronousWait;     

 

  uint32_t FSMC_WaitSignalPolarity;  

 

  uint32_t FSMC_WrapMode;            

 

  uint32_t FSMC_WaitSignalActive;    


 

  uint32_t FSMC_WriteOperation;      
 

  uint32_t FSMC_WaitSignal;          

 

  uint32_t FSMC_ExtendedMode;        
 

  uint32_t FSMC_WriteBurst;          
  

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;    

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;            
}FSMC_NORSRAMInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_SetupTime;      



 

  uint32_t FSMC_WaitSetupTime;  



 

  uint32_t FSMC_HoldSetupTime;  




 

  uint32_t FSMC_HiZSetupTime;   



 
}FSMC_NAND_PCCARDTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;              
 

  uint32_t FSMC_Waitfeature;      
 

  uint32_t FSMC_MemoryDataWidth;  
 

  uint32_t FSMC_ECC;              
 

  uint32_t FSMC_ECCPageSize;      
 

  uint32_t FSMC_TCLRSetupTime;    

 

  uint32_t FSMC_TARSetupTime;     

  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;     

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;  
}FSMC_NANDInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Waitfeature;    
 

  uint32_t FSMC_TCLRSetupTime;  

 

  uint32_t FSMC_TARSetupTime;   

  

  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;    
  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;    
}FSMC_PCCARDInitTypeDef;



 



 



 






 



   




 



     



 



















 



 








 



 

#line 317 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"



 



 








 



 







 
  


 







 
  


 








 



 








 



 








 



 





                              


 



 







 



 









 



 







 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 521 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"



 



 
  


 



 








 




 








 



 

#line 577 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"



 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 653 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"


 



 

#line 669 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_fsmc.h"





 



 



 



 



 



 

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NANDDeInit(uint32_t FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);








 



 



  

 
#line 39 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"




















 

 







 




 



 



 

#line 53 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"
                                     


 

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;





 

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;








 

typedef struct
{
  uint16_t GPIO_Pin;             
 

  GPIOSpeed_TypeDef GPIO_Speed;  
 

  GPIOMode_TypeDef GPIO_Mode;    
 
}GPIO_InitTypeDef;




 

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;





 



 



 

#line 144 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"



#line 163 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"



 



 

#line 204 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"







#line 217 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"






#line 245 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"
                              


  



 

#line 266 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"

#line 274 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"



 



 

#line 299 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"

#line 316 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_gpio.h"



 



  








                                                 


 



 



 



 

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);








 



 



 

 
#line 40 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"




















 

 







 




 



 



 



 

typedef struct
{
  uint32_t I2C_ClockSpeed;          
 

  uint16_t I2C_Mode;                
 

  uint16_t I2C_DutyCycle;           
 

  uint16_t I2C_OwnAddress1;         
 

  uint16_t I2C_Ack;                 
 

  uint16_t I2C_AcknowledgedAddress; 
 
}I2C_InitTypeDef;



  




 





 

#line 92 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"


 



 







  



 







 



 







 



 







  



 

#line 166 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"


 



 







 



 







  



 







  



 







  



 

#line 236 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"



#line 246 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"


 



 



 

#line 265 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"



 

#line 284 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"



#line 298 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"


 



 




 







 
 

























 

 


 





























 

  
 


 
 

 






 
























 

    
 



 



 



























 

  
 

 


 
 


 


 

#line 496 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_i2c.h"


 



 




 



 




 



 



 



 



 

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);













































































 





 
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);




 
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);




 
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);



 

void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);








  



  



  

 
#line 41 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_iwdg.h"




















 

 







 




 



 



 



 



 



 







 



 

#line 84 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_iwdg.h"


 



 







 



 



 



 



 

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);








 



 



 

 
#line 42 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_pwr.h"




















 

 







 




 



  



  



  



  



  

#line 70 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_pwr.h"


 



 







 



 




 


 



 










 



 



 



 



 

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);








 



 



 

 
#line 43 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"




















 

 







 




 



 



 

typedef struct
{
  uint32_t SYSCLK_Frequency;   
  uint32_t HCLK_Frequency;     
  uint32_t PCLK1_Frequency;    
  uint32_t PCLK2_Frequency;    
  uint32_t ADCCLK_Frequency;   
}RCC_ClocksTypeDef;



 



 



 









  



 



#line 94 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"



  



 
#line 126 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"

#line 141 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 
#line 175 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 




 
#line 196 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 

#line 283 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"




 

#line 295 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 

#line 317 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


  



 

#line 333 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 

#line 347 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"

#line 364 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"




 




 








 
#line 396 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


#line 423 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"
  



 

#line 435 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 








 



 

#line 462 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 







#line 489 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"


 



 

#line 518 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"




  



 

#line 553 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"
 




 



 







#line 586 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"



 



 

#line 606 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"

#line 625 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"




 



 



 



 



 

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);





#line 666 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rcc.h"

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);


 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);




void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);






void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);





void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);








 



 



  

 
#line 44 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rtc.h"




















 

 







 




 



  



  



  



 



 

#line 64 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rtc.h"


  



 

#line 82 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_rtc.h"



 



 



 



 



 

void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetPrescaler(uint32_t PrescalerValue);
void RTC_SetAlarm(uint32_t AlarmValue);
uint32_t  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);








 



 



 

 
#line 45 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"




















 

 







 




 



 



 

typedef struct
{
  uint32_t SDIO_ClockEdge;            
 

  uint32_t SDIO_ClockBypass;          

 

  uint32_t SDIO_ClockPowerSave;       

 

  uint32_t SDIO_BusWide;              
 

  uint32_t SDIO_HardwareFlowControl;  
 

  uint8_t SDIO_ClockDiv;              
 
                                           
} SDIO_InitTypeDef;

typedef struct
{
  uint32_t SDIO_Argument;  


 

  uint32_t SDIO_CmdIndex;   

  uint32_t SDIO_Response;  
 

  uint32_t SDIO_Wait;      
 

  uint32_t SDIO_CPSM;      

 
} SDIO_CmdInitTypeDef;

typedef struct
{
  uint32_t SDIO_DataTimeOut;     

  uint32_t SDIO_DataLength;      
 
  uint32_t SDIO_DataBlockSize;  
 
 
  uint32_t SDIO_TransferDir;    

 
 
  uint32_t SDIO_TransferMode;   
 
 
  uint32_t SDIO_DPSM;           

 
} SDIO_DataInitTypeDef;



  



 



 







 



 







  



 







 



 









 



 







 



 






  




 

#line 222 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"


  



 




 



 

#line 245 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"


 



 








 



 






  



 

#line 283 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"


 



 




 



 

#line 330 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"


 



 







 



 







 



 






 



 

#line 421 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"



#line 448 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_sdio.h"





 



 







 



 



 



 



 

void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerState(void);
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
uint32_t SDIO_GetDataCounter(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG);
void SDIO_ClearFlag(uint32_t SDIO_FLAG);
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);








 



 



 

 
#line 46 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"




















 

 







 




 



  



 



 

typedef struct
{
  uint16_t SPI_Direction;           
 

  uint16_t SPI_Mode;                
 

  uint16_t SPI_DataSize;            
 

  uint16_t SPI_CPOL;                
 

  uint16_t SPI_CPHA;                
 

  uint16_t SPI_NSS;                 

 
 
  uint16_t SPI_BaudRatePrescaler;   



 

  uint16_t SPI_FirstBit;            
 

  uint16_t SPI_CRCPolynomial;        
}SPI_InitTypeDef;



 

typedef struct
{

  uint16_t I2S_Mode;         
 

  uint16_t I2S_Standard;     
 

  uint16_t I2S_DataFormat;   
 

  uint16_t I2S_MCLKOutput;   
 

  uint32_t I2S_AudioFreq;    
 

  uint16_t I2S_CPOL;         
 
}I2S_InitTypeDef;



 



 










 
  
#line 136 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


 



 







 



 







  



 







 



 







 



 







  



 

#line 220 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 248 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


 



 

#line 266 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


 



 

#line 282 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 312 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"






  



 







 



 






 



 







 



 






 



 







 



 

#line 396 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


 



 

#line 417 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_spi.h"


 



 




 



 



 



 



 

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);








 



 



 

 
#line 47 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"




















 

 







 




 



  



  




 

typedef struct
{
  uint16_t TIM_Prescaler;         
 

  uint16_t TIM_CounterMode;       
 

  uint16_t TIM_Period;            

  

  uint16_t TIM_ClockDivision;     
 

  uint8_t TIM_RepetitionCounter;  






 
} TIM_TimeBaseInitTypeDef;       



 

typedef struct
{
  uint16_t TIM_OCMode;        
 

  uint16_t TIM_OutputState;   
 

  uint16_t TIM_OutputNState;  

 

  uint16_t TIM_Pulse;         
 

  uint16_t TIM_OCPolarity;    
 

  uint16_t TIM_OCNPolarity;   

 

  uint16_t TIM_OCIdleState;   

 

  uint16_t TIM_OCNIdleState;  

 
} TIM_OCInitTypeDef;



 

typedef struct
{

  uint16_t TIM_Channel;      
 

  uint16_t TIM_ICPolarity;   
 

  uint16_t TIM_ICSelection;  
 

  uint16_t TIM_ICPrescaler;  
 

  uint16_t TIM_ICFilter;     
 
} TIM_ICInitTypeDef;




 

typedef struct
{

  uint16_t TIM_OSSRState;        
 

  uint16_t TIM_OSSIState;        
 

  uint16_t TIM_LOCKLevel;        
  

  uint16_t TIM_DeadTime;         

 

  uint16_t TIM_Break;            
 

  uint16_t TIM_BreakPolarity;    
 

  uint16_t TIM_AutomaticOutput;  
 
} TIM_BDTRInitTypeDef;



 

#line 186 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

 



 






 
#line 205 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"
									                                 
 
#line 216 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

                                             
#line 225 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

 
#line 236 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

 
#line 249 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

                                         
#line 266 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

 
#line 279 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"
                                                                                                                                                                                                                          


  



 

#line 308 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


 



 







  



 

#line 341 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 355 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


 



 

#line 373 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 







 



 
  






 



 







  



 







  



 







  



 







  



 







  



 







  



 







  



 

#line 497 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 







 



 







  



 







  



 







  



 

#line 561 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 577 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 593 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 610 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"

#line 619 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 665 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 709 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 725 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"



  



 

#line 742 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 770 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 784 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



  






 



 







  



 







  



 

#line 833 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  




 

#line 851 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"



  



 

#line 866 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 







  



 





                                     


  



 







  



 

#line 927 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 

#line 943 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


  



 







  



 

#line 987 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"
                               
                               



  



 




  



 




  



 

#line 1034 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_tim.h"


 



 



 



  



 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);








  



  



 

 
#line 48 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"




















 

 







 




 



  



  



  
  
typedef struct
{
  uint32_t USART_BaudRate;            


 

  uint16_t USART_WordLength;          
 

  uint16_t USART_StopBits;            
 

  uint16_t USART_Parity;              




 
 
  uint16_t USART_Mode;                
 

  uint16_t USART_HardwareFlowControl; 

 
} USART_InitTypeDef;



  
  
typedef struct
{

  uint16_t USART_Clock;   
 

  uint16_t USART_CPOL;    
 

  uint16_t USART_CPHA;    
 

  uint16_t USART_LastBit; 

 
} USART_ClockInitTypeDef;



  



  
  
















  
  


                                    




  



  
  
#line 146 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"


  



  
  
#line 160 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"


  



  
  





  



  
#line 187 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"


  



  






  



 
  






  



 







 



 







  



 
  
#line 264 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"


 



 







  



 







 



 
  







 



 







  



 

#line 336 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"
                              
#line 344 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_usart.h"



  



  



  



  



 

void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);








  



  



  

 
#line 49 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_wwdg.h"




















 

 







 




 



  



  
  


  



  
  


  
  
#line 68 "D:\\stm32_trial\\FWlib\\inc\\stm32f10x_wwdg.h"



  



  



  


  



  
  
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);









  



  



  

 
#line 50 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"
#line 1 "D:\\stm32_trial\\FWlib\\inc\\misc.h"




















 

 







 




 



 



 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;
 


 



 
























 



 



 



 







 



 

#line 133 "D:\\stm32_trial\\FWlib\\inc\\misc.h"


 



 

#line 151 "D:\\stm32_trial\\FWlib\\inc\\misc.h"















 



 







 



 



 



 



 

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 



 

 
#line 51 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"

 
 

 
 

 
#line 74 "D:\\stm32_trial\\Project\\..\\User\\stm32f10x_conf.h"



 
#line 8300 "D:\\stm32_trial\\Project\\..\\CMSIS\\stm32f10x.h"




 

















 









 

  

 

 
#line 33 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"



 



 



 



 

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;  

  uint32_t DMA_MemoryBaseAddr;      

  uint32_t DMA_DIR;                
 

  uint32_t DMA_BufferSize;         

 

  uint32_t DMA_PeripheralInc;      
 

  uint32_t DMA_MemoryInc;          
 

  uint32_t DMA_PeripheralDataSize; 
 

  uint32_t DMA_MemoryDataSize;     
 

  uint32_t DMA_Mode;               


 

  uint32_t DMA_Priority;           
 

  uint32_t DMA_M2M;                
 
}DMA_InitTypeDef;



 



 

#line 107 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"



 







 



 







 



 







 



 

#line 154 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"


 



 

#line 168 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"


 



 






 



 

#line 195 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"


 



 







 



 






#line 248 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"

#line 269 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"



#line 296 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"



 



 
#line 332 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"

#line 353 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"



#line 380 "D:\\stm32_trial\\Project\\..\\FWlib\\inc\\stm32f10x_dma.h"


 



 





 



 



 



 



 

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber); 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
void DMA_ClearFlag(uint32_t DMAy_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);








 



 



 

 
#line 24 "D:\\stm32_trial\\FWlib\\src\\stm32f10x_dma.c"




 




  



  


 



 


 
#line 55 "D:\\stm32_trial\\FWlib\\src\\stm32f10x_dma.c"

 






 


 




 



 



 



 



 



 



 



 







 
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
   
  ((void)0);
  
   
  DMAy_Channelx->CCR &= (uint16_t)(~((uint16_t)0x0001));
  
   
  DMAy_Channelx->CCR  = 0;
  
   
  DMAy_Channelx->CNDTR = 0;
  
   
  DMAy_Channelx->CPAR  = 0;
  
   
  DMAy_Channelx->CMAR = 0;
  
  if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0008)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00000001) | ((uint32_t)0x00000002) | ((uint32_t)0x00000004) | ((uint32_t)0x00000008)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x001C)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00000010) | ((uint32_t)0x00000020) | ((uint32_t)0x00000040) | ((uint32_t)0x00000080)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0030)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00000100) | ((uint32_t)0x00000200) | ((uint32_t)0x00000400) | ((uint32_t)0x00000800)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0044)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00001000) | ((uint32_t)0x00002000) | ((uint32_t)0x00004000) | ((uint32_t)0x00008000)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0058)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00010000) | ((uint32_t)0x00020000) | ((uint32_t)0x00040000) | ((uint32_t)0x00080000)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x006C)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x00100000) | ((uint32_t)0x00200000) | ((uint32_t)0x00400000) | ((uint32_t)0x00800000)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0080)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR |= ((uint32_t)(((uint32_t)0x01000000) | ((uint32_t)0x02000000) | ((uint32_t)0x04000000) | ((uint32_t)0x08000000)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0408)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR |= ((uint32_t)(((uint32_t)0x00000001) | ((uint32_t)0x00000002) | ((uint32_t)0x00000004) | ((uint32_t)0x00000008)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x041C)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR |= ((uint32_t)(((uint32_t)0x00000010) | ((uint32_t)0x00000020) | ((uint32_t)0x00000040) | ((uint32_t)0x00000080)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0430)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR |= ((uint32_t)(((uint32_t)0x00000100) | ((uint32_t)0x00000200) | ((uint32_t)0x00000400) | ((uint32_t)0x00000800)));
  }
  else if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0444)))
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR |= ((uint32_t)(((uint32_t)0x00001000) | ((uint32_t)0x00002000) | ((uint32_t)0x00004000) | ((uint32_t)0x00008000)));
  }
  else
  { 
    if (DMAy_Channelx == ((DMA_Channel_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0458)))
    {
       
      ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR |= ((uint32_t)(((uint32_t)0x00010000) | ((uint32_t)0x00020000) | ((uint32_t)0x00040000) | ((uint32_t)0x00080000)));
    }
  }
}









 
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

   
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);   
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);

 
   
  tmpreg = DMAy_Channelx->CCR;
   
  tmpreg &= ((uint32_t)0xFFFF800F);
   
   
   
   
   
   
   
   
   
  tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

   
  DMAy_Channelx->CCR = tmpreg;

 
   
  DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;

 
   
  DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

 
   
  DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}






 
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
 
   
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
   
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
   
  DMA_InitStruct->DMA_DIR = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_BufferSize = 0;
   
  DMA_InitStruct->DMA_PeripheralInc = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_MemoryInc = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_PeripheralDataSize = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_MemoryDataSize = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_Mode = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_Priority = ((uint32_t)0x00000000);
   
  DMA_InitStruct->DMA_M2M = ((uint32_t)0x00000000);
}








 
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
   
  ((void)0);
  ((void)0);

  if (NewState != DISABLE)
  {
     
    DMAy_Channelx->CCR |= ((uint16_t)0x0001);
  }
  else
  {
     
    DMAy_Channelx->CCR &= (uint16_t)(~((uint16_t)0x0001));
  }
}














 
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
   
  ((void)0);
  ((void)0);
  ((void)0);
  if (NewState != DISABLE)
  {
     
    DMAy_Channelx->CCR |= DMA_IT;
  }
  else
  {
     
    DMAy_Channelx->CCR &= ~DMA_IT;
  }
}









 
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber)
{
   
  ((void)0);
  
 
   
  DMAy_Channelx->CNDTR = DataNumber;  
}








 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
   
  ((void)0);
   
  return ((uint16_t)(DMAy_Channelx->CNDTR));
}






















































 
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  
   
  ((void)0);

   
  if ((DMAy_FLAG & ((uint32_t)0x10000000)) != (uint32_t)RESET)
  {
     
    tmpreg = ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->ISR ;
  }
  else
  {
     
    tmpreg = ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->ISR ;
  }

   
  if ((tmpreg & DMAy_FLAG) != (uint32_t)RESET)
  {
     
    bitstatus = SET;
  }
  else
  {
     
    bitstatus = RESET;
  }
  
   
  return  bitstatus;
}






















































 
void DMA_ClearFlag(uint32_t DMAy_FLAG)
{
   
  ((void)0);

   
  if ((DMAy_FLAG & ((uint32_t)0x10000000)) != (uint32_t)RESET)
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR = DMAy_FLAG;
  }
  else
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR = DMAy_FLAG;
  }
}






















































 
ITStatus DMA_GetITStatus(uint32_t DMAy_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

   
  ((void)0);

   
  if ((DMAy_IT & ((uint32_t)0x10000000)) != (uint32_t)RESET)
  {
     
    tmpreg = ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->ISR;
  }
  else
  {
     
    tmpreg = ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->ISR;
  }

   
  if ((tmpreg & DMAy_IT) != (uint32_t)RESET)
  {
     
    bitstatus = SET;
  }
  else
  {
     
    bitstatus = RESET;
  }
   
  return  bitstatus;
}






















































 
void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{
   
  ((void)0);

   
  if ((DMAy_IT & ((uint32_t)0x10000000)) != (uint32_t)RESET)
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0400))->IFCR = DMAy_IT;
  }
  else
  {
     
    ((DMA_TypeDef *) ((((uint32_t)0x40000000) + 0x20000) + 0x0000))->IFCR = DMAy_IT;
  }
}



 



 



 

 
