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
#include "ui.h"


void main_app(void)
{  
    ui_init();

    // --- Main loop ---
    while (1)
    {
        ui_update();
    }
}

