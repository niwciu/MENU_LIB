#include "pushbutton_GPIO_interface.h"
#include "stm32g0xx.h"


static void key_up_gpio_init(void);
static PB_input_state_t get_key_up_state(void);
static void key_down_gpio_init(void);
static PB_input_state_t get_key_down_state(void);
static void key_enter_gpio_init(void);
static PB_input_state_t get_key_enter_state(void);
static void key_esc_gpio_init(void);
static PB_input_state_t get_key_esc_state(void);

PB_driver_interface_t KEY_UP_GPIO_interface_struct = {
    key_up_gpio_init,
    get_key_up_state,
};
/*************** For more pusbuttons *************/
PB_driver_interface_t KEY_DOWN_GPIO_interface_struct = {
    key_down_gpio_init,
    get_key_down_state,
};

PB_driver_interface_t KEY_ENTER_GPIO_interface_struct = {
    key_enter_gpio_init,
    get_key_enter_state,
};

PB_driver_interface_t KEY_ESC_GPIO_interface_struct = {
    key_esc_gpio_init,
    get_key_esc_state,
};

static void key_up_gpio_init(void)
{
    //init key_1 gpio
    //clk init
    RCC -> IOPENR |= RCC_IOPENR_GPIOBEN;
    // pin as input
    GPIOB->MODER &=(~GPIO_MODER_MODE10_Msk);
}

static PB_input_state_t get_key_up_state(void)
{
    PB_input_state_t PB_state=UNKNOWN;
    if (GPIOB->IDR & GPIO_IDR_ID10_Msk) 
    {
        PB_state= RELEASED;
    }
    else 
    {
        PB_state=PUSHED;
    }
    return PB_state;
}

static void key_down_gpio_init(void)
{
    //clk init
    RCC -> IOPENR |= RCC_IOPENR_GPIOBEN;

    // pin as input
    GPIOB->MODER &=(~GPIO_MODER_MODE2_Msk);
    
}

static PB_input_state_t get_key_down_state(void)
{
    PB_input_state_t PB_state=UNKNOWN;
    if (GPIOB->IDR & GPIO_IDR_ID2_Msk) 
    {
        PB_state= RELEASED;
    }
    else 
    {
        PB_state=PUSHED;
    }
    return PB_state;
}

static void key_enter_gpio_init(void)
{
    //clk init
    RCC -> IOPENR |= RCC_IOPENR_GPIOBEN;
    // pin as input
    GPIOB->MODER &=(~GPIO_MODER_MODE11_Msk);
}

static PB_input_state_t get_key_enter_state(void)
{
    PB_input_state_t PB_state=UNKNOWN;
    if (GPIOB->IDR & GPIO_IDR_ID11_Msk) 
    {
        PB_state= RELEASED;
    }
    else 
    {
        PB_state=PUSHED;
    }
    return PB_state;
}

static void key_esc_gpio_init(void)
{
    //clk init
    RCC -> IOPENR |= RCC_IOPENR_GPIOBEN;
    // pin as input
    GPIOB->MODER &=(~GPIO_MODER_MODE1_Msk);
}

static PB_input_state_t get_key_esc_state(void)
{
    PB_input_state_t PB_state=UNKNOWN;
    if (GPIOB->IDR & GPIO_IDR_ID1_Msk) 
    {
        PB_state= RELEASED;
    }
    else 
    {
        PB_state=PUSHED;
    }
    return PB_state;
}
/************************************************/

PB_driver_interface_t *PB_up_driver_interface_get(void)
{
    return &KEY_UP_GPIO_interface_struct;
}

PB_driver_interface_t *PB_down_driver_interface_get(void)
{
    return &KEY_DOWN_GPIO_interface_struct;
}

const PB_driver_interface_t *PB_enter_driver_interface_get(void)
{
    return &KEY_ENTER_GPIO_interface_struct;
}

const PB_driver_interface_t *PB_esc_driver_interface_get(void)
{
    return &KEY_ESC_GPIO_interface_struct;
}