#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit MCPU-Variable to suit STM32 project requirements.
#        For debug build using Unix Makefiles:
#          cmake -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug all (optional with VERBOSE=1  and -jxx ->xx numnber of cores)
#        For debug build using Ninja:
#          cmake -S ./ -B Debug -G"Ninja" -DCMAKE_BUILD_TYPE=Debug
#          ninja -C Debug (optional with -V  and -jxx ->xx numnber of cores)
# 
#        For release build Unix Makefiles:
#          cmake -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make all -C Release VERBOSE=1 -j12 (optional with VERBOSE=1  and -jxx ->xx numnber of cores)
#        For Release build using Ninja:
#          cmake -S ./ -B Release -G"Ninja" -DCMAKE_BUILD_TYPE=Release
#          ninja -C Release (optional -V  and -jxx ->xx numnber of cores)
#############################################################################################################################
cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ../config/STM32/Toolchain-arm-gcc.cmake)

# Allow assembler
enable_language(ASM)

project(STM32G070RB_HAL_LL)


set(INCLUDE_DIRS
    ./Core/Inc
    ./Core/Startup

    ./Drivers/CMSIS/Include
    ./Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ./Drivers/STM32G0xx_HAL_Driver/Inc

    ../../src
    ../../src/ui
    .
)

set(C_SRCS
    ./Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_exti.c
    ./Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_gpio.c
    ./Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_pwr.c
    ./Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c
    ./Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_utils.c

    ./Core/Src/main.c
    ./Core/Src/stm32g0xx_it.c
    ./Core/Src/syscalls.c
    ./Core/Src/sysmem.c
    ./Core/Src/system_stm32g0xx.c
    ./Core/Src/tim_delay.c

    ./Core/Src/pushbutton_GPIO_interface.c
    ./Core/Src/lcd_hd44780_GPIO_interface.c

    ../../src/main_app.c

    ../../src/ui/menu.c
    ../../src/ui/keypad.c
    ../../src/ui/menu_screen_driver_interface.c

)

set(ASM_SRCS
    ./Core/Startup/startup_stm32g070rbtx.s
)

set(GLOBAL_DEFINES
    -DBUILD_TYPE=${BUILD_TYPE}
    -DSTM32G070xx 
    -DUSE_FULL_LL_DRIVER 
    -DHSE_VALUE=8000000 
    -DHSE_STARTUP_TIMEOUT=100 
    -DLSE_STARTUP_TIMEOUT=5000 
    -DLSE_VALUE=32768 
    -DEXTERNAL_CLOCK_VALUE=48000 
    -DHSI_VALUE=16000000 
    -DLSI_VALUE=32000 
    -DVDD_VALUE=3300 
    -DPREFETCH_ENABLE=1 
    -DINSTRUCTION_CACHE_ENABLE=1 
    -DDATA_CACHE_ENABLE=1
)

set(LINKED_LIBS
    menu_lib
    pushbutton_lib
    lib_lcd_hd44780
)


include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

set(MCPU "-mcpu=cortex-m0plus")
set(LD_FILE ./STM32G070RBTX_FLASH.ld)
include(    ../config/STM32/compiler_flags.cmake)

add_subdirectory(../../lib/LCD_HD44780 lib_lcd_hd44780_build)
add_subdirectory(../../lib/PUSHBUTTON_SWITCH_LIB pushbutton_lib_build)
add_subdirectory(../../lib/MENU_LIB menu_lib_build)

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LINKED_LIBS})
