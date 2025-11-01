/**
 * @file menu_lib.h
 * @author niwciu
 * @brief Public API for the menu library.
 * @version 1.0.0
 * @date 2025-10-27
 *
 * This header provides the public interface for initializing and controlling
 * a hierarchical menu system displayed on an external screen driver.
 *
 * The module provides functions to initialize the menu engine, navigate through
 * menu items, and update the displayed view.
 *
 * @copyright Copyright (c) 2025
 *
 * @ingroup MenuLib
 */

#ifndef _MENU_LIB_
#define _MENU_LIB_

#ifdef __cplusplus
extern "C"
{
#endif

#include "menu.h"
#include "menu_lib_type.h"
#include <stdint.h>

    /**
     * @typedef menu_exit_cb_t
     * @brief Callback type for handling top-level menu exit.
     *
     * The callback function is called when the user exits the top-level menu.
     */
    typedef void (*menu_exit_cb_t)(void);

    /**
     * @brief Initialize the menu engine and display driver interface.
     *
     * This function must be called before any other menu operations.
     * It initializes the display driver interface and validates required
     * function pointers.
     *
     * @return menu_status_t Status of the initialization:
     * - MENU_OK — Initialization successful.
     * - MENU_ERR_NO_DISPLAY_INTERFACE — Display driver interface not found.
     * - MENU_ERR_INCOMPLETE_INTERFACE — Display driver functions missing.
     */
    menu_status_t menu_init(void);

    /**
     * @brief Initialize and display a menu view.
     *
     * Sets up the initial menu state, validates the menu structure,
     * and displays the first screen of the given root menu.
     *
     * @param root_menu Pointer to the root of the menu tree.
     * @param menu_exit_cb Callback function invoked when exiting the top-level menu.
     * @param custom_menu_header Optional string for a custom menu header (can be NULL).
     * @return menu_status_t Status of the view initialization:
     * - MENU_OK — View initialized successfully.
     * - MENU_ERR_NOT_INITIALIZED — Menu system not initialized (menu_init() not called).
     * - MENU_ERR_NO_MENU — Root menu pointer is NULL.
     * - MENU_ERR_MENU_TOO_DEEP — Menu depth exceeds MAX_MENU_DEPTH.
     */
    menu_status_t menu_view_init(menu_t *root_menu, menu_exit_cb_t menu_exit_cb, const char *custom_menu_header);

    /**
     * @brief Move selection to the next menu item.
     *
     * Advances the cursor to the next menu item if available.
     * If the end of the list is reached, the cursor does not move.
     */
    void menu_next(void);

    /**
     * @brief Move selection to the previous menu item.
     *
     * Moves the cursor to the previous menu item if available.
     * If the beginning of the list is reached, the cursor does not move.
     */
    void menu_prev(void);

    /**
     * @brief Enter submenu or execute callback.
     *
     * - If the current item has a child, opens its submenu.
     * - If the item has a callback, executes it.
     */
    void menu_enter(void);

    /**
     * @brief Exit submenu or close the menu system.
     *
     * - If in a submenu, returns to the parent menu.
     * - If at the top level, calls the top-level exit callback (if provided).
     */
    void menu_esc(void);

    /**
     * @brief Refresh the screen view.
     *
     * Re-draws the current menu view on the display.
     * This function is typically called internally but can also be used
     * after external display updates.
     */
    void update_screen_view(void);

    /**
     * @brief Get the current menu position pointer.
     *
     * Returns a pointer to the currently selected menu item.
     *
     * @return menu_t* Pointer to the current menu item.
     */
    menu_t *get_current_menu_position(void);

#ifdef __cplusplus
}
#endif    /* __cplusplus */
#endif    /* _MENU_LIB_ */
/** @} */ /* end of MenuLib group */
