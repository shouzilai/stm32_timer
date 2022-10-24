#line 1 "D:\\stm32_trial\\CMSIS\\core_cm3.c"
 




















 

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


 

























































































 



































 
#line 25 "D:\\stm32_trial\\CMSIS\\core_cm3.c"

 
#line 34 "D:\\stm32_trial\\CMSIS\\core_cm3.c"

#line 44 "D:\\stm32_trial\\CMSIS\\core_cm3.c"


 

#line 256 "D:\\stm32_trial\\CMSIS\\core_cm3.c"
 
#pragma diag_suppress=Pe940







 
uint32_t __get_PSP(void)
{
  __asm("mrs r0, psp");
  __asm("bx lr");
}








 
void __set_PSP(uint32_t topOfProcStack)
{
  __asm("msr psp, r0");
  __asm("bx lr");
}








 
uint32_t __get_MSP(void)
{
  __asm("mrs r0, msp");
  __asm("bx lr");
}








 
void __set_MSP(uint32_t topOfMainStack)
{
  __asm("msr msp, r0");
  __asm("bx lr");
}








 
uint32_t __REV16(uint16_t value)
{
  __asm("rev16 r0, r0");
  __asm("bx lr");
}








 
uint32_t __RBIT(uint32_t value)
{
  __asm("rbit r0, r0");
  __asm("bx lr");
}








 
uint8_t __LDREXB(uint8_t *addr)
{
  __asm("ldrexb r0, [r0]");
  __asm("bx lr"); 
}








 
uint16_t __LDREXH(uint16_t *addr)
{
  __asm("ldrexh r0, [r0]");
  __asm("bx lr");
}








 
uint32_t __LDREXW(uint32_t *addr)
{
  __asm("ldrex r0, [r0]");
  __asm("bx lr");
}









 
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
  __asm("strexb r0, r0, [r1]");
  __asm("bx lr");
}









 
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
  __asm("strexh r0, r0, [r1]");
  __asm("bx lr");
}









 
uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
  __asm("strex r0, r0, [r1]");
  __asm("bx lr");
}

#pragma diag_default=Pe940


