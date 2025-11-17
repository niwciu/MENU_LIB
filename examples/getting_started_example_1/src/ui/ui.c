/**
 * @file ui.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "keypad.h"
#include "lcd_hd44780.h"
#include "menu_lib.h"
#include "menu_handlers.h"

// #include <stddef.h>

void ui_init(void)
{
    // Initialize MENU_LIB (fetches display interface and validates it and initialize the lcd)
    menu_init();

    // turn on lcd backlight
    lcd_enable_backlight();

    // Initialize keypad/UI (ENTER enters the menu) and bind main app keys functionality
    keypad_init();
    keypad_bind_main_app_controls();
    // Print main app label
    set_UI_main_app_scr();
} 

void ui_update(void)
{
    // Process debounced buttons; drives MENU_LIB when in menu mode
    keypad_process();

    // Keep the display refreshed when buffering is enabled
    lcd_update();
} 




