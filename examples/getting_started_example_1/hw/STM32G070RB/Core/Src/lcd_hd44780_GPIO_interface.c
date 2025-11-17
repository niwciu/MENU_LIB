/**
 * @file lcd_hd44780_GPIO_interface.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "stm32g070xx.h"
#include "lcd_hd44780_GPIO_interface.h"
#include "lcd_hd44780_config.h"
#include "tim_delay.h"


// clang-format off
#define ON   1
#define OFF  0

/*********************************Define hardware connection in your project*******************************/
#define LCD_D7_PORT         GPIOD
#define LCD_D6_PORT         GPIOD
#define LCD_D5_PORT         GPIOD
#define LCD_D4_PORT         GPIOD
#define LCD_RS_PORT         GPIOB
#define LCD_E_PORT          GPIOB
#define LCD_BCKL_PORT       GPIOC
#if USE_RW_PIN == ON
#define LCD_RW_PORT          GPIOB
#endif

#define LCD_D7_PORT_CLK_EN      RCC_IOPENR_GPIODEN
#define LCD_D6_PORT_CLK_EN      RCC_IOPENR_GPIODEN
#define LCD_D5_PORT_CLK_EN      RCC_IOPENR_GPIODEN
#define LCD_D4_PORT_CLK_EN      RCC_IOPENR_GPIODEN
#define LCD_RS_PORT_CLK_EN      RCC_IOPENR_GPIOBEN
#define LCD_E_PORT_CLK_EN       RCC_IOPENR_GPIOBEN
#define LCD_BCKL_PORT_CLK_EN    RCC_IOPENR_GPIOCEN
#if USE_RW_PIN == ON
#define LCD_RW_PORT_CLK_EN      RCC_IOPENR_GPIOBEN
#endif

#define LCD_D7_OUT_PIN      GPIO_ODR_OD3
#define LCD_D6_OUT_PIN      GPIO_ODR_OD2
#define LCD_D5_OUT_PIN      GPIO_ODR_OD1
#define LCD_D4_OUT_PIN      GPIO_ODR_OD0
#define LCD_RS_OUT_PIN      GPIO_ODR_OD13
#define LCD_E_OUT_PIN       GPIO_ODR_OD15
#define LCD_BCKL_OUT_PIN    GPIO_ODR_OD7
#if USE_RW_PIN == ON
#define LCD_RW_OUT_PIN       GPIO_ODR_OD14
#endif

#define LCD_D7_IN_PIN       GPIO_IDR_ID3
#define LCD_D6_IN_PIN       GPIO_IDR_ID2
#define LCD_D5_IN_PIN       GPIO_IDR_ID1
#define LCD_D4_IN_PIN       GPIO_IDR_ID0

#define MODER_LCD_D7_0      GPIO_MODER_MODE3_0
#define MODER_LCD_D7_Msk    GPIO_MODER_MODE3_Msk
#define MODER_LCD_D6_0      GPIO_MODER_MODE2_0
#define MODER_LCD_D6_Msk    GPIO_MODER_MODE2_Msk
#define MODER_LCD_D5_0      GPIO_MODER_MODE1_0
#define MODER_LCD_D5_Msk    GPIO_MODER_MODE1_Msk
#define MODER_LCD_D4_0      GPIO_MODER_MODE0_0
#define MODER_LCD_D4_Msk    GPIO_MODER_MODE0_Msk
#define MODER_LCD_RS_0      GPIO_MODER_MODE13_0
#define MODER_LCD_RS_Msk    GPIO_MODER_MODE13_Msk
#define MODER_LCD_E_0       GPIO_MODER_MODE15_0
#define MODER_LCD_E_Msk     GPIO_MODER_MODE15_Msk
#define MODER_LCD_BCKL_0    GPIO_MODER_MODE7_0
#define MODER_LCD_BCKL_Msk  GPIO_MODER_MODE7_Msk
#if USE_RW_PIN == ON
#define MODER_LCD_RW_0      GPIO_MODER_MODE14_0
#define MODER_LCD_RW_Msk    GPIO_MODER_MODE14_Msk
#endif
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
static void wraper_delay_us(uint32_t delay_us);
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
    wraper_delay_us,
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
    RCC -> IOPENR |= LCD_D7_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D6_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D5_PORT_CLK_EN;
    RCC -> IOPENR |= LCD_D4_PORT_CLK_EN;
    
    set_LCD_DATA_PINS_as_outputs();
    init_LCD_SIGNAL_PINS_as_outputs();
    init_LCD_BCKL_PIN_as_output();
    //disable LCD backlight on init
    LCD_BCKL_PORT->ODR &= ~LCD_BCKL_OUT_PIN;

}

static void set_LCD_DATA_PINS_as_outputs(void)
{
    LCD_D7_PORT->MODER &=(~MODER_LCD_D7_Msk);
    LCD_D7_PORT->MODER |= MODER_LCD_D7_0;

    LCD_D6_PORT->MODER &=(~MODER_LCD_D6_Msk);
    LCD_D6_PORT->MODER |= MODER_LCD_D6_0;

    LCD_D5_PORT->MODER &=(~MODER_LCD_D5_Msk);
    LCD_D5_PORT->MODER |= MODER_LCD_D5_0;

    LCD_D4_PORT->MODER &=(~MODER_LCD_D4_Msk);
    LCD_D4_PORT->MODER |= MODER_LCD_D4_0;

}
static void set_LCD_DATA_PINS_as_inputs(void)
{
    LCD_D7_PORT->MODER &=(~MODER_LCD_D7_Msk);

    LCD_D6_PORT->MODER &=(~MODER_LCD_D6_Msk);

    LCD_D5_PORT->MODER &=(~MODER_LCD_D5_Msk);

    LCD_D4_PORT->MODER &=(~MODER_LCD_D4_Msk);
}

static void set_LCD_DATA_PINS_state(uint8_t data)
{
    if ((data & LCD_D4_MASK))
        LCD_D4_PORT->ODR |= LCD_D4_OUT_PIN;
    else
        LCD_D4_PORT->ODR &= ~LCD_D4_OUT_PIN;

    if ((data & LCD_D5_MASK))
        LCD_D5_PORT->ODR |= LCD_D5_OUT_PIN;
    else
        LCD_D5_PORT->ODR &= ~LCD_D5_OUT_PIN;

    if ((data & LCD_D6_MASK))
        LCD_D6_PORT->ODR |= LCD_D6_OUT_PIN;
    else
        LCD_D6_PORT->ODR &= ~LCD_D6_OUT_PIN;

    if ((data & LCD_D7_MASK))
        LCD_D7_PORT->ODR |= LCD_D7_OUT_PIN;
    else
        LCD_D7_PORT->ODR &= ~LCD_D7_OUT_PIN;
}

static uint8_t get_LCD_DATA_PINS_state(void)
{
    uint8_t data = 0;
    if (((LCD_D4_PORT->IDR) & LCD_D4_IN_PIN) == LCD_D4_IN_PIN)
        data = LCD_D4_MASK;
    if (((LCD_D5_PORT->IDR) & LCD_D5_IN_PIN) == LCD_D5_IN_PIN)
        data |= LCD_D5_MASK;
    if (((LCD_D6_PORT->IDR) & LCD_D6_IN_PIN) == LCD_D6_IN_PIN)
        data |= LCD_D6_MASK;
    if (((LCD_D7_PORT->IDR) & LCD_D7_IN_PIN) == LCD_D7_IN_PIN)
        data |= LCD_D7_MASK;
    return data;
}

static void wraper_delay_us(uint32_t delay_us)
{
    _delay_us(delay_us);
}

static void set_LCD_E(void)
{
    LCD_E_PORT->ODR |= LCD_E_OUT_PIN;
}
static void reset_LCD_E(void)
{
    LCD_E_PORT->ODR &= ~LCD_E_OUT_PIN;
}
static void set_LCD_RS(void)
{
    LCD_RS_PORT->ODR |= LCD_RS_OUT_PIN;
}
static void reset_LCD_RS(void)
{
    LCD_RS_PORT->ODR &= ~LCD_RS_OUT_PIN;
}
static void set_LCD_RW(void)
{
    LCD_RW_PORT->ODR |= LCD_RW_OUT_PIN;
}
static void reset_LCD_RW(void)
{
    LCD_RW_PORT->ODR &= ~LCD_RW_OUT_PIN;
}
static void set_LCD_BCKL(void)
{
    LCD_BCKL_PORT->ODR |= LCD_BCKL_OUT_PIN;
}
static void reset_LCD_BCKL(void)
{
    LCD_BCKL_PORT->ODR &= ~LCD_BCKL_OUT_PIN;
}

static void init_LCD_SIGNAL_PINS_as_outputs(void)
{
    RCC -> IOPENR |= LCD_RS_PORT_CLK_EN;
    LCD_RS_PORT->MODER &=(~MODER_LCD_RS_Msk);
    LCD_RS_PORT->MODER |= MODER_LCD_RS_0;

    RCC -> IOPENR |= LCD_E_PORT_CLK_EN;
    LCD_E_PORT->MODER &=(~MODER_LCD_E_Msk);
    LCD_E_PORT->MODER |= MODER_LCD_E_0;

#if USE_RW_PIN == 1
    RCC -> IOPENR |= LCD_RW_PORT_CLK_EN;
    LCD_RW_PORT->MODER &=(~MODER_LCD_RW_Msk);
    LCD_RW_PORT->MODER |= MODER_LCD_RW_0;
#endif
}

static void init_LCD_BCKL_PIN_as_output(void)
{
    RCC -> IOPENR |= LCD_BCKL_PORT_CLK_EN;
    LCD_BCKL_PORT->MODER &=(~MODER_LCD_BCKL_Msk);
    LCD_BCKL_PORT->MODER |= MODER_LCD_BCKL_0;
}