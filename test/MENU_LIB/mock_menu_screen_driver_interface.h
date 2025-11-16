/**
 * @file mock_menu_screen_driver_interface.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <stdint.h>

#define LCD_X 20
#define LCD_Y 4

typedef enum
{
    MENU_SCREEN_INIT_OK,
    MENU_SCREEN_INIT_UNKNOWN,
} mock_menu_screen_init_status_e;

extern char mock_lcd_screen[LCD_Y][LCD_X];
extern char *mock_screen_lines[LCD_Y];
extern uint8_t mock_cur_lcd_x;
extern uint8_t mock_cur_lcd_y;
extern mock_menu_screen_init_status_e mock_menu_screen_init_status;

void init_mock_screen_driver(void);
void deinit_mock_screen_driver(void);
void init_mock_incomplete_screen_driver(void);