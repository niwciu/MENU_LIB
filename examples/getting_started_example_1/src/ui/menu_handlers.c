/**
 * @file menu_internal.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-11-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "menu_handlers.h"
#include "lcd_hd44780.h"
#include "keypad.h"
#include "menu_lib.h"

#include <stddef.h>

static uint8_t brightness = 5; // demo state 0..20

/** menu_handlers internal function declarations */
static void on_menu_enter(void);
static void on_menu_exit(void);
static void keypad_bind_menu_controls(void);

/** menu info static section handlers */
static void info_exit_cb(void);

/** menu brightness static section handlers */
static void br_up(void);
static void br_down(void);
static void br_apply(void);
static void br_exit(void);
static void update_lcd_br_view(void);

/** UI comon basic menu handlers  */
void set_UI_main_app_scr(void)
{
    lcd_buf_locate(LINE_2, C6);
    lcd_buf_str("Example  1");
    lcd_buf_locate(LINE_3, C3);
    lcd_buf_str("Main App. Screen");
}

void keypad_bind_main_app_controls(void)
{
    // Main app mode: only ENTER enters the menu
    keypad_bind_conrtol_handlers(NULL, NULL, on_menu_enter, NULL);
}

/** main app UI functionality API */
void lcd_brightness_enter_cb(void)
{
    keypad_bind_conrtol_handlers(br_up, br_down, br_apply, br_exit);
    enable_keypad_up_down_repetition();

    lcd_buf_cls();
    lcd_buf_locate(LINE_1, C4);
    lcd_buf_str("LCD Brightness");
    lcd_buf_locate(LINE_3, C1);
    update_lcd_br_view();
}

/** menu enter calback section */
void info_enter_cb(void)
{
    keypad_bind_conrtol_handlers(NULL, NULL, NULL, NULL);

    lcd_buf_cls();
    lcd_buf_locate(LINE_1, C5);
    lcd_buf_str("Device info:");
    lcd_buf_locate(LINE_2, C7);
    lcd_buf_str("FW 1.0.0");
    lcd_buf_locate(LINE_3, C5);
    lcd_buf_str("Build:  demo");
    lcd_buf_locate(LINE_4, C6);
    lcd_buf_str("<ESC> back");
    keypad_bind_conrtol_handlers(NULL, NULL, NULL, info_exit_cb);
}

/** general menu_handlers internall functions */
static void on_menu_enter(void)
{
    // Start menu view at top-level; default header (NULL)
    // Root pointer is the first top-level item (menu_1) from the generator
    menu_view_init(&menu_1, on_menu_exit, NULL);
    keypad_bind_menu_controls();
}
static void on_menu_exit(void)
{
    lcd_buf_cls();
    keypad_bind_main_app_controls();
    set_UI_main_app_scr();
}

static void keypad_bind_menu_controls(void)
{
    keypad_bind_conrtol_handlers(menu_prev, menu_next, menu_enter, menu_esc);
}

/** menu info static section handlers */
static void info_exit_cb(void)
{
    lcd_buf_cls();
    keypad_bind_menu_controls();
    update_screen_view();
}

/** menu settings section handlers */
static void br_up(void)
{
    if (brightness < 20)
    {
        brightness++;
    }
    lcd_brightness_enter_cb();
}
static void br_down(void)
{
    if (brightness > 0)
    {
        brightness--;
    }
    lcd_brightness_enter_cb();
}
static void br_apply(void)
{
    /* TODO: apply to real backlight driver */
    // after applying new setings go back to menu
    br_exit();
}
static void br_exit(void)
{
    lcd_buf_cls();
    disable_keypad_up_down_repetition();
    keypad_bind_menu_controls();
    update_screen_view(); // refresh where user left off
}
static void update_lcd_br_view(void)
{
    // Simple bar visualization (20 chars wide)
    char line[21];
    for (uint8_t i = 0; i < 20; ++i)
        line[i] = (i < brightness) ? '*' : '-';
    line[20] = '\0';
    lcd_buf_str(line);
}
