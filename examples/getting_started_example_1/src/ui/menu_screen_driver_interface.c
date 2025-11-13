/**
 * @file menu_screen_driver_interface.c
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "lcd_hd44780.h"
#include "lcd_hd44780_config.h"
#include "menu_screen_driver_interface.h"

// --- Callback declarations ---
static uint8_t get_screen_lines(void);
static uint8_t get_screen_columns(void);

// --- LCD driver interface definition ---
const struct menu_screen_driver_interface_struct display_driver = {
    .screen_init = lcd_init,
    .clr_scr = lcd_cls,
    .cursor_position = (void (*)(uint8_t, uint8_t))lcd_locate,
    .print_string = lcd_str,
    .print_char = lcd_char,
    .get_number_of_screen_lines = get_screen_lines,
    .get_number_of_chars_per_line = get_screen_columns
};

// --- Callback definitions ---
static uint8_t get_screen_lines(void)  
{ 
    return LCD_Y; 
}
static uint8_t get_screen_columns(void)
{ 
    return LCD_X; 
}

// --- Accessor function for MENU_LIB ---
const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void)
{
    return &display_driver;
}