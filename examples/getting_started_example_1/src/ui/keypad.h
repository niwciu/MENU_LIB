/**
 * @file keypad.h
 * @author niwciu (niwciu@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef UI_KEYPAD_H_
#define UI_KEYPAD_H_

#ifdef __cplusplus
extern "C" {
#endif

void keypad_init(void);       // create buttons, register default (app) callbacks
void keypad_process(void);    // poll buttons; call periodically in main loop
void set_UI_main_app_scr(void); // draw default app screen (label/info)
void update_keypad_repetition_counters(void); 

#ifdef __cplusplus
}
#endif
#endif /* UI_KEYPAD_H_ */