/**
 * @file main.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "menu_lib.h"
#include "menu.h"          // generated in Step 3
#include "keypad.h"        // created in Step 2
#include "lcd_hd44780.h"      // for lcd_update() when buffering is ON
#include "lcd_hd44780_config.h"

void main_app(void)
{
    // Initialize MENU_LIB (fetches display interface and validates it)
    
    // lcd_init();
    menu_init();
    lcd_enable_backlight();
    // Initialize keypad/UI (ENTER enters the menu)
    keypad_init();

    // Print main app label
    set_UI_main_app_scr();
    

    // --- Main loop ---
    for (;;)
    {
        // Process debounced buttons; drives MENU_LIB when in menu mode
        keypad_process();

        // Keep the display refreshed when buffering is enabled
        lcd_update();
    }
}

void SysTick_Handler(void)
{
    update_keypad_repetition_counters();
}