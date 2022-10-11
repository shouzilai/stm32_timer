SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Altium Designer Summer 09\System;C:\Program Files (x86)\IDM Computer Solutions\UltraEdit\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=TIM3-DEMO
SET CPU_CLOCK=0x007A1200
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f10x_it.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\led.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\time_test.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\misc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f10x_tim.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\core_cm3.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\system_stm32f10x.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\STM32-DEMO.lnp"
C:\Keil\ARM\ARMCC\bin\fromelf.exe ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"
