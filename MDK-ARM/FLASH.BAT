SET PATH=D:\Keil_v5\ARM\ARMCLANG\Bin;D:\Program Files (x86)\STMicroelectronics\st_toolset\asm;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;D:\ProgramData\Anaconda3;D:\ProgramData\Anaconda3\Library\mingw-w64\bin;D:\ProgramData\Anaconda3\Library\usr\bin;D:\ProgramData\Anaconda3\Library\bin;D:\ProgramData\Anaconda3\Scripts;D:\VMware\bin\;C:\Program Files\Microsoft MPI\Bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files\CMake\bin;D:\Program Files\Matlab\Matlab_ R2021a(64bit)\Matlab\runtime\win64;D:\Program Files\Matlab\Matlab_ R2021a(64bit)\Matlab\bin;D:\Program Files\Matlab\Matlab_ R2021a(64bit)\Matlab\polyspace\bin;D:\Program Files\NASM;C:\Program Files\Microsoft SQL Server\150\Tools\Binn\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\;D:\Program Files\Git\cmd;D;C:\Program Files\Docker\Docker\resources\bin;C:\ProgramData\DockerDesktop\version-bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Users\YEWAN\AppData\Local\Microsoft\WindowsApps;C:\Users\YEWAN\.dotnet\tools;C:\Users\YEWAN\mingw64\bin;C:\Program Files\CMake\bin;D:\Program Files\JetBrains\PyCharm 2021.3.3\bin;;D:\Program Files\doxygen\bin;D:\gcc-arm-none-eabi\bin;D:\OpenOCD\bin;D:\VScode\Microsoft VS Code\bin;C:\Users\YEWAN\.vscode\extensions\actboy168.lua-debug-1.59.0-win32-x64\runtime\win32-x64\lua-latest;
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=FLASH
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\startup_stm32f10x_hd._ac"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\misc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\stm32f10x_gpio.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\stm32f10x_rcc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\main.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\stm32f10x_it.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\system_stm32f10x.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\sys.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\delay.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"..\obj\led.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "..\Obj\FreeRTOS-Transplant.lnp"
"D:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" "..\Obj\FreeRTOS-Transplant.axf" --i32combined --output "..\Obj\FreeRTOS-Transplant.hex"
