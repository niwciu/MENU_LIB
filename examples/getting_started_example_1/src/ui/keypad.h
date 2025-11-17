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

typedef void(*key_action_cb_t)(void);

void keypad_init(void);       // create buttons, register default (app) callbacks
void keypad_process(void);    // poll buttons; call periodically in main loop
void update_keypad_debounce_timers(void); 

// Bind custom handlers to keypad
void keypad_bind_conrtol_handlers( key_action_cb_t on_up, key_action_cb_t on_down, key_action_cb_t on_enter, key_action_cb_t on_esc);
void enable_keypad_up_down_repetition(void);
void disable_keypad_up_down_repetition(void);


#ifdef __cplusplus
}
#endif
#endif /* UI_KEYPAD_H_ */