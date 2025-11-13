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
#include "menu_lib.h"
#include "lcd_hd44780.h"
#include "lcd_hd44780_config.h"
#include "menu.h"               // generated in Step 3

#include <stdio.h>

// Four navigation buttons
static PUSHBUTTON_TypDef btn_up;
static PUSHBUTTON_TypDef btn_down;
static PUSHBUTTON_TypDef btn_enter;
static PUSHBUTTON_TypDef btn_esc;

// Forward declarations
static void on_menu_enter(void);
static void on_menu_exit(void);
static void keypad_bind_menu_controls(void);
static void keypad_bind_main_app_controls(void);

void keypad_init(void)
{
    // All buttons: trigger on push, no repetition
    init_pushbutton(&btn_up,    REPETITION_OFF, TRIGGER_ON_PUSH, PB_up_driver_interface_get);
    init_pushbutton(&btn_down,  REPETITION_OFF, TRIGGER_ON_PUSH, PB_down_driver_interface_get);
    init_pushbutton(&btn_enter, REPETITION_OFF, TRIGGER_ON_PUSH, PB_enter_driver_interface_get);
    init_pushbutton(&btn_esc,   REPETITION_OFF, TRIGGER_ON_PUSH, PB_esc_driver_interface_get);

    keypad_bind_main_app_controls();
}

void keypad_process(void)
{
    // Poll debounced state machines; call from main loop
    check_pushbutton(&btn_up);
    check_pushbutton(&btn_down);
    check_pushbutton(&btn_enter);
    check_pushbutton(&btn_esc);
}

void set_UI_main_app_scr(void)
{
    lcd_buf_locate(LINE_2, C6);
    lcd_buf_str("Example  1");
    lcd_buf_locate(LINE_3, C4);
    lcd_buf_str("default mode");
}

static void on_menu_enter(void)
{
    // Start menu view at top-level; default header (NULL)
    // Root pointer is the first top-level item (menu_1) from the generator
    menu_view_init(&menu_1, on_menu_exit, NULL);
    keypad_bind_menu_controls();
}

static void on_menu_exit(void)
{
    lcd_cls();
    keypad_bind_main_app_controls();
    set_UI_main_app_scr();
}

static void keypad_bind_menu_controls(void)
{
    // UP -> previous item, DOWN -> next item
    register_button_push_callback(&btn_up,    menu_prev);
    register_button_push_callback(&btn_down,  menu_next);
    register_button_push_callback(&btn_enter, menu_enter);
    register_button_push_callback(&btn_esc,   menu_esc);
}

static void keypad_bind_main_app_controls(void)
{
    // Main app mode: only ENTER enters the menu
    register_button_push_callback(&btn_up,    NULL);
    register_button_push_callback(&btn_down,  NULL);
    register_button_push_callback(&btn_enter, on_menu_enter);
    register_button_push_callback(&btn_esc,   NULL);
}