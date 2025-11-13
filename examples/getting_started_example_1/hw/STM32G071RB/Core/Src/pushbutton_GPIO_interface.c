#include "pushbutton_GPIO_interface.h"


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
/************************************************/

static void key_up_gpio_init(void)
{
    //init key_1 gpio
}

static PB_input_state_t get_key_up_state(void)
{
    PB_input_state_t PB_state=UNKNOWN;
    //check state and retunr proper state according to project assumptions
    return PB_state;
}
/*************** For more pusbuttons *************/
static void key_down_gpio_init(void)
{
    
}

static PB_input_state_t get_key_down_state(void)
{
    PB_input_state_t test=UNKNOWN;
    //check state and retunr proper state according to project assumptions
    return test;
}

static void key_enter_gpio_init(void)
{
    
}

static PB_input_state_t get_key_enter_state(void)
{
    PB_input_state_t test=UNKNOWN;
    //check state and retunr proper state according to project assumptions
    return test;
}

static void key_esc_gpio_init(void)
{
    
}

static PB_input_state_t get_key_esc_state(void)
{
    PB_input_state_t test=UNKNOWN;
    //check state and retunr proper state according to project assumptions
    return test;
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