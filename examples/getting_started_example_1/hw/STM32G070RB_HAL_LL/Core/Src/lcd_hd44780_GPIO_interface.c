/*
 * @Author: lukasz.niewelt
 * @Date: 2023-12-07 15:51:41
 * @Last Modified by: lukasz.niewelt
 * @Last Modified time: 2023-12-08 00:34:48
 */
#include <stdio.h>
#include "lcd_hd44780_GPIO_interface.h"
#include "main.h"
#include "tim_delay.h"


// clang-format off
#define ON   1
#define OFF  0

#define LCD_DATA_PORT GPIOD
#define LCD_SIG_PORT GPIOB

/*********************************Define hardware connection in your project*******************************/
// ToDo define here name of lcd PINS and it's hardware represetation 
//  #define LCD_D4 xx
//  #define LCD_D5 xx
//  etc
/****************************END OFF define hardware connection in your application***********************/

#define LCD_D4_MASK         0x01
#define LCD_D5_MASK         0x02
#define LCD_D6_MASK         0x04
#define LCD_D7_MASK         0x08
// clang-format on

static void init_LCD_data_and_SIG_pins(void);
static void set_LCD_DATA_PINS_as_outputs(void);
static void set_LCD_DATA_PINS_as_inputs(void);
static void set_LCD_DATA_PINS_state(uint8_t data);
static uint8_t get_LCD_DATA_PINS_state(void);
static void delay_us(uint32_t delay_us);
static void set_LCD_E(void);
static void reset_LCD_E(void);
static void set_LCD_RS(void);
static void reset_LCD_RS(void);
static void set_LCD_RW(void);
static void reset_LCD_RW(void);
static void set_LCD_BCKL(void);
static void reset_LCD_BCKL(void);
static void init_LCD_SIGNAL_PINS_as_outputs(void);
static void init_LCD_BCKL_PIN_as_output(void);

/************LCD_IO_driver_interface implementation START**************/
static const struct LCD_IO_driver_interface_struct LCD_IO_driver = {
    init_LCD_data_and_SIG_pins,
    set_LCD_DATA_PINS_as_outputs,
    set_LCD_DATA_PINS_as_inputs,
    set_LCD_DATA_PINS_state,
    get_LCD_DATA_PINS_state,
    delay_us,
    set_LCD_E,
    reset_LCD_E,
    set_LCD_RS,
    reset_LCD_RS,
    set_LCD_RW,
    reset_LCD_RW,
    set_LCD_BCKL,
    reset_LCD_BCKL,
};
const struct LCD_IO_driver_interface_struct *LCD_IO_driver_interface_get(void)
{
    return &LCD_IO_driver;
}

/*************LCD_IO_driver_interface implementation END***************/

static void init_LCD_data_and_SIG_pins(void)
{
    // enable clk on LCD gpio pins
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
    //configure gpio pins
    set_LCD_DATA_PINS_as_outputs();
    init_LCD_SIGNAL_PINS_as_outputs();
    init_LCD_BCKL_PIN_as_output();
    set_LCD_BCKL();
}

static void set_LCD_DATA_PINS_as_outputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as output
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LCD_DB7_Pin |LCD_DB6_Pin | LCD_DB5_Pin | LCD_DB4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);

}
static void set_LCD_DATA_PINS_as_inputs(void)
{
// configure LCD_D4, LCD_D5, LCD_D6, LCD_D7 as input
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LCD_DB7_Pin | LCD_DB6_Pin | LCD_DB5_Pin | LCD_DB4_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(LCD_DATA_PORT, &GPIO_InitStruct);
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
    // Initialize LCD_E LCD_RS and optionl LCD_RW GPIOs as outputs
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LCD_E_Pin |LCD_RW_Pin | LCD_RS_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_SIG_PORT, &GPIO_InitStruct);
}

static void init_LCD_BCKL_PIN_as_output(void)
{
// Initialize LCD_BCKL GPIO as outputs
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LCD_BCKL_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(LCD_BCKL_GPIO_Port, &GPIO_InitStruct);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LL_GPIO_SetOutputPin(LCD_DB4_GPIO_Port, LCD_DB4_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DB4_GPIO_Port, LCD_DB4_Pin);

    if ((data & LCD_D5_MASK))
        LL_GPIO_SetOutputPin(LCD_DB5_GPIO_Port, LCD_DB5_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DB5_GPIO_Port, LCD_DB5_Pin);

    if ((data & LCD_D6_MASK))
        LL_GPIO_SetOutputPin(LCD_DB6_GPIO_Port, LCD_DB6_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DB6_GPIO_Port, LCD_DB6_Pin);
    if ((data & LCD_D7_MASK))
        LL_GPIO_SetOutputPin(LCD_DB7_GPIO_Port, LCD_DB7_Pin);
    else
        LL_GPIO_ResetOutputPin(LCD_DB7_GPIO_Port, LCD_DB7_Pin);
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (LL_GPIO_IsInputPinSet(LCD_DB4_GPIO_Port, LCD_DB4_Pin))
        data = LCD_D4_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DB5_GPIO_Port, LCD_DB5_Pin))
        data |= LCD_D5_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DB6_GPIO_Port, LCD_DB6_Pin))
        data |= LCD_D6_MASK;
    if (LL_GPIO_IsInputPinSet(LCD_DB7_GPIO_Port, LCD_DB7_Pin))
        data |= LCD_D7_MASK;
    return data;
}

static void set_LCD_E(void)
{
    LL_GPIO_SetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin);
}
static void reset_LCD_E(void)
{
    LL_GPIO_ResetOutputPin(LCD_E_GPIO_Port, LCD_E_Pin);
}
static void set_LCD_RS(void)
{
    LL_GPIO_SetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
}
static void reset_LCD_RS(void)
{
    LL_GPIO_ResetOutputPin(LCD_RS_GPIO_Port, LCD_RS_Pin);
}
static void set_LCD_RW(void)
{
    LL_GPIO_SetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin);
}
static void reset_LCD_RW(void)
{
    LL_GPIO_ResetOutputPin(LCD_RW_GPIO_Port, LCD_RW_Pin);
}
static void set_LCD_BCKL(void)
{
    LL_GPIO_SetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}
static void reset_LCD_BCKL(void)
{
    LL_GPIO_ResetOutputPin(LCD_BCKL_GPIO_Port, LCD_BCKL_Pin);
}

static void delay_us(uint32_t delay_us)
{
    _delay_us(delay_us);
}


