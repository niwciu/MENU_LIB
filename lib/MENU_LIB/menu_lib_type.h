/**
 * @file menu_lib_type.h
 * @author niwciu
 * @brief Type definitions for the menu library.
 * @version 1.0.0
 * @date 2025-02-07
 *
 * This header defines core data types used by the menu library,
 * including menu status codes and the menu item structure.
 *
 * @copyright Copyright (c) 2025
 *
 * @ingroup MenuLib
 */

#ifndef _MENU_LIB_TYPE_
#define _MENU_LIB_TYPE_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**
     * @enum menu_status_t
     * @brief Status codes for the menu module.
     *
     * Enumerates all possible return values for menu-related functions,
     * including initialization of the menu system and individual menu views.
     */
    typedef enum
    {
        MENU_OK = 0,                       /**< Operation successful */
        MENU_ERR_NO_DISPLAY_INTERFACE = 1, /**< Display driver not initialized or missing */
        MENU_ERR_INCOMPLETE_INTERFACE = 2, /**< Display driver missing required function pointers */
        MENU_ERR_NOT_INITIALIZED = 3,      /**< Menu system not initialized (menu_init() not called) */
        MENU_ERR_NO_MENU = 4,              /**< Root menu pointer is NULL */
        MENU_ERR_MENU_TOO_DEEP = 5,        /**< Menu depth exceeds MAX_MENU_DEPTH */
        MENU_ERR_NULL_MENU_ITEM = 6        /**< Encountered NULL menu item pointer during view update */
    } menu_status_t;

    /**
     * @struct menu_t
     * @brief Represents a single menu item in a hierarchical menu system.
     *
     * Each menu item is part of a doubly linked list on the same menu level
     * and can optionally point to a submenu (child) or its parent menu for multi-level navigation.
     * A callback function can be assigned to a menu item to execute specific functionality
     * when the item is selected.
     */
    typedef struct menu_t
    {
        const char *name;       /**< Name of the menu item (displayed on the screen). */
        struct menu_t *next;    /**< Pointer to the next menu item on the same level. */
        struct menu_t *prev;    /**< Pointer to the previous menu item on the same level. */
        struct menu_t *child;   /**< Pointer to the submenu (child menu) of this item. */
        struct menu_t *parent;  /**< Pointer to the parent menu of this item. */
        void (*callback)(void); /**< Callback function executed when the menu item is selected. */
    } menu_t;

#ifdef __cplusplus
}
#endif    /* __cplusplus */
#endif    /* _MENU_LIB_TYPE_ */
/** @} */ /* end of MenuLib group */