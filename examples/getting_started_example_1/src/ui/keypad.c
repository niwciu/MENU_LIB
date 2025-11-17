/**
 * @file keypad.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "keypad.h"
#include "pushbutton.h"

#include <stdio.h>

// Four navigation buttons
static PUSHBUTTON_TypDef btn_up;
static PUSHBUTTON_TypDef btn_down;
static PUSHBUTTON_TypDef btn_enter;
static PUSHBUTTON_TypDef btn_esc;



void keypad_init(void)
{
    // All buttons: trigger on push, no repetition
    init_pushbutton(&btn_up,    REPETITION_OFF, TRIGGER_ON_PUSH, PB_up_driver_interface_get);
    init_pushbutton(&btn_down,  REPETITION_OFF, TRIGGER_ON_PUSH, PB_down_driver_interface_get);
    init_pushbutton(&btn_enter, REPETITION_OFF, TRIGGER_ON_PUSH, PB_enter_driver_interface_get);
    init_pushbutton(&btn_esc,   REPETITION_OFF, TRIGGER_ON_PUSH, PB_esc_driver_interface_get);
}

void keypad_process(void)
{
    // Poll debounced state machines; call from main loop
    check_pushbutton(&btn_up);
    check_pushbutton(&btn_down);
    check_pushbutton(&btn_enter);
    check_pushbutton(&btn_esc);
}

void update_keypad_debounce_timers(void)
{
    dec_pushbutton_deb_rep_timer(&btn_up);
    dec_pushbutton_deb_rep_timer(&btn_down);
    dec_pushbutton_deb_rep_timer(&btn_enter);
    dec_pushbutton_deb_rep_timer(&btn_esc);

}

void keypad_bind_conrtol_handlers( key_action_cb on_up, key_action_cb on_down, key_action_cb on_enter, key_action_cb on_esc)
{
    register_button_push_callback(&btn_up,    on_up);
    register_button_push_callback(&btn_down,  on_down);
    register_button_push_callback(&btn_enter, on_enter);
    register_button_push_callback(&btn_esc,   on_esc);
}
void enable_keypad_up_down_repetition(void)
{
    enable_pusbutton_repetition(&btn_up);
    enable_pusbutton_repetition(&btn_down);
}
void disable_keypad_up_down_repetition(void)
{
    disable_pusbutton_repetition(&btn_up);
    disable_pusbutton_repetition(&btn_down);
}
