/**
 * @file menu.c
 * @author LCD menu code generator
 * @brief Generated menu definitions
 * @date 2025-11-02
 */
#include "menu.h"
#include "keypad.h"
#include "lcd_hd44780.h"
#include <stddef.h>

static void info_cb(void);
static void lcd_brightness_cb(void);
static void sound_cb(void);
static void start_cb(void);
static void stop_cb(void);
static void about_cb(void);

menu_t menu_1 = {"Info", &menu_2, NULL, NULL, NULL, info_cb};
menu_t menu_2 = {"Settings", &menu_3, &menu_1, &menu_2_1, NULL, NULL};
menu_t menu_2_1 = {"LCD Brightness", &menu_2_2, NULL, NULL, &menu_2, lcd_brightness_cb};
menu_t menu_2_2 = {"Sound", NULL, &menu_2_1, NULL, &menu_2, sound_cb};
menu_t menu_3 = {"Action", &menu_4, &menu_2, &menu_3_1, NULL, NULL};
menu_t menu_3_1 = {"Start", &menu_3_2, NULL, NULL, &menu_3, start_cb};
menu_t menu_3_2 = {"Stop", NULL, &menu_3_1, NULL, &menu_3, stop_cb};
menu_t menu_4 = {"About", NULL, &menu_3, NULL, NULL, about_cb};

static void info_cb(void)
{ /* TODO: implement */
    set_info_keypad_functionality();
    // show info screen
    lcd_buf_cls();
    lcd_buf_locate(LINE_1,C9);
    lcd_buf_str("INFO");
    lcd_buf_locate(LINE_2,C4);
    lcd_buf_str("screen content");
    lcd_buf_locate(LINE_4,C2);
    lcd_buf_str("press ESC to exit.");

}
static void lcd_brightness_cb(void)
{ /* TODO: implement */
}
static void sound_cb(void)
{ /* TODO: implement */
}
static void start_cb(void)
{ /* TODO: implement */
}
static void stop_cb(void)
{ /* TODO: implement */
}
static void about_cb(void)
{ /* TODO: implement */
}