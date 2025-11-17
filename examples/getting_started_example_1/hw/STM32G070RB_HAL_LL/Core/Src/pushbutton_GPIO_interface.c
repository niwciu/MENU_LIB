#include "pushbutton_GPIO_interface.h"
#include "main.h"

static void key_up_gpio_init(void);
static void key_down_gpio_init(void);
static void key_esc_gpio_init(void);
static void key_enter_gpio_init(void);
static void key_func_gpio_init(void);
static PB_input_state_t get_key_up_gpio_state(void);
static PB_input_state_t get_key_down_gpio_state(void);
static PB_input_state_t get_key_esc_gpio_state(void);
static PB_input_state_t get_key_enter_gpio_state(void);
static PB_input_state_t get_key_func_gpio_state(void);

static PB_input_state_t get_pulled_up_pushbutton_gpio_state(GPIO_TypeDef *GPIO_Port, uint32_t GPIO_Pin);



PB_driver_interface_t KEY_UP_GPIO_interface_struct = {
    key_up_gpio_init,
    get_key_up_gpio_state,
};
PB_driver_interface_t KEY_DOWN_GPIO_interface_struct = {
    key_down_gpio_init,
    get_key_down_gpio_state,
};
PB_driver_interface_t KEY_ESC_GPIO_interface_struct = {
    key_esc_gpio_init,
    get_key_esc_gpio_state,
};
PB_driver_interface_t KEY_ENTER_GPIO_interface_struct = {
    key_enter_gpio_init,
    get_key_enter_gpio_state,
};
PB_driver_interface_t KEY_FUNC_GPIO_interface_struct = {
    key_func_gpio_init,
    get_key_func_gpio_state,
};

const PB_driver_interface_t *PB_up_driver_interface_get(void)
{
    return &KEY_UP_GPIO_interface_struct;
}
const PB_driver_interface_t *PB_down_driver_interface_get(void)
{
    return &KEY_DOWN_GPIO_interface_struct;
}
const PB_driver_interface_t *PB_esc_driver_interface_get(void)
{
    return &KEY_ESC_GPIO_interface_struct;
}
const PB_driver_interface_t *PB_enter_driver_interface_get(void)
{
    return &KEY_ENTER_GPIO_interface_struct;
}
// const PB_driver_interface_t *pushbutton_FUNC_GPIO_interface_get(void)
// {
//     return &KEY_FUNC_GPIO_interface_struct;
// }

static void key_up_gpio_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    
    GPIO_InitStruct.Pin = UP_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(UP_GPIO_Port, &GPIO_InitStruct);
    
}
static void key_down_gpio_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

    GPIO_InitStruct.Pin = DOWN_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(DOWN_GPIO_Port, &GPIO_InitStruct);
}
static void key_esc_gpio_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);    
    
    GPIO_InitStruct.Pin = ESC_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(ESC_GPIO_Port, &GPIO_InitStruct);
}
static void key_enter_gpio_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB); 

    GPIO_InitStruct.Pin = ENTER_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(ENTER_GPIO_Port, &GPIO_InitStruct);  
}
static void key_func_gpio_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB); 

    GPIO_InitStruct.Pin = FUNC_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(FUNC_GPIO_Port, &GPIO_InitStruct);  
}

static PB_input_state_t get_key_up_gpio_state(void)
{
    return get_pulled_up_pushbutton_gpio_state(UP_GPIO_Port,UP_Pin);
}

static PB_input_state_t get_key_down_gpio_state(void)
{
    return get_pulled_up_pushbutton_gpio_state(DOWN_GPIO_Port,DOWN_Pin);  
}

static PB_input_state_t get_key_esc_gpio_state(void)
{
    return get_pulled_up_pushbutton_gpio_state(ESC_GPIO_Port,ESC_Pin);
}

static PB_input_state_t get_key_enter_gpio_state(void)
{
    return get_pulled_up_pushbutton_gpio_state(ENTER_GPIO_Port,ENTER_Pin);
}

static PB_input_state_t get_key_func_gpio_state(void)
{
    PB_input_state_t pin_state=UNKNOWN;
    if (LL_GPIO_IsInputPinSet(FUNC_GPIO_Port,FUNC_Pin)) 
    {
        pin_state= PUSHED;
    }
    else 
    {
        pin_state=RELEASED;
    }
    return pin_state;
}

static PB_input_state_t get_pulled_up_pushbutton_gpio_state(GPIO_TypeDef *GPIO_Port, uint32_t GPIO_Pin)
{
    PB_input_state_t pin_state=UNKNOWN;
    if (LL_GPIO_IsInputPinSet(GPIO_Port,GPIO_Pin)) 
    {
        pin_state= RELEASED;
    }
    else 
    {
        pin_state=PUSHED;
    }
    return pin_state;
}
