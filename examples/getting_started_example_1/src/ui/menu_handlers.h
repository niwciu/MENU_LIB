/**
 * @file menu_handlers.h
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef _MENU_HANDLERS_H_
#define _MENU_HANDLERS_H_

#ifdef __cplusplus
extern "C" {
#endif


/** UI main app handlers  */
void set_UI_main_app_scr(void);
void keypad_bind_main_app_controls(void);

/** menu enter callbacks */
void info_enter_cb(void);
void lcd_brightness_enter_cb(void);
void sound_enter_cb(void);
void start_enter_cb(void);
void stop_enter_cb(void);
void about_enter_cb(void);



#ifdef __cplusplus
}
#endif
#endif /* _MENU_HANDLERS_H_ */