/**
 * @file menu_lib.c
 * @author niwciu (niwciu@gmail.com)
 * @brief Implementation of hierarchical menu library with display driver abstraction.
 * @version 1.0.0
 * @date 2025-10-27
 *
 * Provides menu initialization, navigation, and rendering logic for embedded systems.
 * Includes validation of menu depth, screen drawing, and safe handling of pointers.
 *
 * @copyright Copyright (c) 2025
 *
 * @ingroup MenuLib
 * @{
 */

#include "menu_lib.h"
#include "menu.h"
#include "menu_screen_driver_interface.h"
#include <string.h>
#include <stdbool.h>

#ifndef UNIT_TESTS
#define PRIVATE static
#else
#define PRIVATE
#endif

/* --- Constants --- */
#define ADDITIONAL_SPACE_CHAR_QTY 2U  /**< Space padding in submenu headers */
#define DEFAULT_MENU_HEADER_COLUMN 7U /**< Default column for centered header text */
#define STRING_START_POSITION 1U      /**< Column index for text after cursor marker */
#define CURSOR_COLUMN_POSITION 0U     /**< Column index of cursor marker '>' */
#define FIRST_ROW 0U                  /**< Index of the first display row */
#define MENU_VIEW_FIRST_ROW 1U        /**< First row used for displaying menu items */
#define FIRST_COLUMN 0U               /**< Index of the first display column */
#define HEADER_ROW_OFFSET 1U          /**< Offset between header and menu view */

/* --- Internal state --- */
PRIVATE bool menu_initialized = false; /**< Indicates if menu system has been initialized */

PRIVATE uint8_t menu_number_of_chars_per_line;
PRIVATE uint8_t menu_number_of_screen_lines;

static menu_t *current_menu_pointer;
static menu_t *menu_item_2_print = NULL;
static menu_t *menu_1st_item = NULL;

static uint8_t cursor_selection_menu_index[MAX_MENU_DEPTH];
static uint8_t cursor_row_position[MAX_MENU_DEPTH];
static uint8_t menu_level;

PRIVATE const struct menu_screen_driver_interface_struct *DISPLAY = NULL;
static menu_exit_cb_t menu_top_level_exit_cb = NULL;

static const char *default_header = " MENU ";
static const char *custom_header = NULL;

/* --- Private function declarations --- */
static bool validate_display_interface(const struct menu_screen_driver_interface_struct *disp);
static uint8_t compute_menu_depth(const menu_t *menu);
static menu_status_t validate_menu_view(const menu_t *root_menu);
static void initialize_menu_view_state(menu_t *root_menu, menu_exit_cb_t menu_exit_cb, const char *custom_menu_header);
static void display_menu_header(void);
static void display_main_menu_header(void);
static void display_sub_menu_header(void);
static void fill_header_with_dashes(void);
static void clear_current_menu_view_with_cursor(void);
static void update_menu_item_pointer_to_print(void);
static void update_current_menu_view_with_cursor(void);
static void display_cursor_marker_if_needed(uint8_t row);
// static void display_error_line(uint8_t row, const char *msg);
static void display_menu_item_name(uint8_t row, const char *name);

/* --- Implementation --- */

/**
 * @brief Initialize the menu system and display interface.
 *
 * Validates that a display driver is available and that all required
 * function pointers are implemented.
 *
 * @return menu_status_t
 * - MENU_OK — Initialization successful
 * - MENU_ERR_NO_DISPLAY_INTERFACE — Display driver interface missing
 * - MENU_ERR_INCOMPLETE_INTERFACE — Display driver missing required functions
 */
menu_status_t menu_init(void)
{
    menu_status_t status = MENU_OK;

    DISPLAY = get_menu_display_driver_interface();

    if (DISPLAY == NULL)
    {
        status = MENU_ERR_NO_DISPLAY_INTERFACE;
    }
    else if (!validate_display_interface(DISPLAY))
    {
        status = MENU_ERR_INCOMPLETE_INTERFACE;
    }
    else
    {
        menu_number_of_chars_per_line = DISPLAY->get_number_of_chars_per_line();
        menu_number_of_screen_lines = DISPLAY->get_number_of_screen_lines();
        DISPLAY->screen_init();
    }

    menu_initialized = (status == MENU_OK);
    return status;
}

/**
 * @brief Initialize and display a menu view.
 *
 * Performs validation of menu structure and prepares the screen for rendering.
 * Initializes cursor, header, and root menu pointers.
 *
 * @param root_menu Pointer to the root menu.
 * @param menu_exit_cb Callback executed when the top-level menu is exited.
 * @param custom_menu_header Optional custom header string (NULL for default).
 * @return menu_status_t
 * - MENU_OK — Menu view successfully initialized
 * - MENU_ERR_NOT_INITIALIZED — Menu engine not initialized
 * - MENU_ERR_NO_MENU — root_menu pointer is NULL
 * - MENU_ERR_MENU_TOO_DEEP — Menu depth exceeds MAX_MENU_DEPTH
 */
menu_status_t menu_view_init(menu_t *root_menu, menu_exit_cb_t menu_exit_cb, const char *custom_menu_header)
{
    menu_status_t status = validate_menu_view(root_menu);

    if (status == MENU_OK)
    {
        initialize_menu_view_state(root_menu, menu_exit_cb, custom_menu_header);
    }

    return status;
}

/**
 * @brief Move cursor to the next menu item.
 *
 * If the next menu item exists, updates the current pointer,
 * cursor selection index, and screen row position.
 */
void menu_next(void)
{
    if (current_menu_pointer->next != NULL)
    {
        current_menu_pointer = current_menu_pointer->next;
        cursor_selection_menu_index[menu_level]++;
        if (cursor_row_position[menu_level] < (menu_number_of_screen_lines - 2U))
        {
            cursor_row_position[menu_level]++;
        }
        update_screen_view();
    }
}

/**
 * @brief Move cursor to the previous menu item.
 *
 * If the previous menu item exists, updates the current pointer,
 * cursor selection index, and screen row position.
 */
void menu_prev(void)
{
    if (current_menu_pointer->prev != NULL)
    {
        current_menu_pointer = current_menu_pointer->prev;
        cursor_selection_menu_index[menu_level]--;
        if (cursor_row_position[menu_level] != 0U)
        {
            cursor_row_position[menu_level]--;
        }
        update_screen_view();
    }
}

/**
 * @brief Enter submenu or execute item callback.
 *
 * If current item has a child menu, descend into submenu.
 * Otherwise, execute the callback function if present.
 */
void menu_enter(void)
{
    if (current_menu_pointer->child != NULL)
    {
        menu_level++;
        if (menu_level < MAX_MENU_DEPTH)
        {
            current_menu_pointer = current_menu_pointer->child;
            cursor_selection_menu_index[menu_level] = 0U;
            cursor_row_position[menu_level] = 0U;
        }
        else
        {
            menu_level--;
        }
        update_screen_view();
    }
    else if (current_menu_pointer->callback != NULL)
    {
        current_menu_pointer->callback();
    }
}

/**
 * @brief Exit current submenu or call top-level exit callback.
 *
 * Moves up one menu level if possible, or calls the top-level exit callback.
 */
void menu_esc(void)
{
    if (current_menu_pointer->parent != NULL)
    {
        menu_level--;
        current_menu_pointer = current_menu_pointer->parent;
        update_screen_view();
    }
    else if (menu_top_level_exit_cb != NULL)
    {
        menu_top_level_exit_cb();
    }
}

/**
 * @brief Refresh the current screen view.
 *
 * Updates header, clears menu area, adjusts item pointers,
 * and redraws menu items including cursor.
 */
void update_screen_view(void)
{
    display_menu_header();
    clear_current_menu_view_with_cursor();
    update_menu_item_pointer_to_print();
    update_current_menu_view_with_cursor();
}

/**
 * @brief Get pointer to the currently selected menu item.
 *
 * @return menu_t* Pointer to the current menu.
 */
menu_t *get_current_menu_position(void)
{
    return current_menu_pointer;
}

/* --- Private helper functions --- */

/**
 * @brief Validate display driver interface.
 *
 * Checks that all required function pointers are non-NULL.
 *
 * @param disp Pointer to the display driver interface.
 * @return true if valid, false otherwise.
 */
static bool validate_display_interface(const struct menu_screen_driver_interface_struct *disp)
{
    return (disp != NULL) &&
           (disp->get_number_of_chars_per_line != NULL) &&
           (disp->get_number_of_screen_lines != NULL) &&
           (disp->cursor_position != NULL) &&
           (disp->print_string != NULL) &&
           (disp->print_char != NULL);
}

/**
 * @brief Recursively compute menu depth.
 *
 * Determines maximum depth of menu tree starting from given node.
 *
 * @param menu Pointer to a menu item.
 * @return uint8_t Depth level (1 for leaf node, 0 for NULL).
 */
static uint8_t compute_menu_depth(const menu_t *menu)
{
    uint8_t depth = 0U;

    if (menu != NULL)
    {
        uint8_t max_child_depth = 0U;
        const menu_t *child = menu->child;

        while (child != NULL)
        {
            uint8_t child_depth = compute_menu_depth(child);
            if (child_depth > max_child_depth)
            {
                max_child_depth = child_depth;
            }
            child = child->next;
        }

        depth = 1U + max_child_depth;
    }

    return depth;
}

/**
 * @brief Validate menu view configuration.
 *
 * Ensures engine is initialized, the menu root is valid,
 * and the menu depth does not exceed the maximum allowed.
 *
 * @param root_menu Pointer to the root menu.
 * @return menu_status_t Validation result.
 */
static menu_status_t validate_menu_view(const menu_t *root_menu)
{
    menu_status_t status = MENU_OK;

    if (!menu_initialized)
    {
        status = MENU_ERR_NOT_INITIALIZED;
    }
    else if (root_menu == NULL)
    {
        status = MENU_ERR_NO_MENU;
    }
    else if (compute_menu_depth(root_menu) > MAX_MENU_DEPTH)
    {
        status = MENU_ERR_MENU_TOO_DEEP;
    }

    return status;
}

/**
 * @brief Initialize menu view internal state.
 *
 * Sets current menu, first item, cursor positions, and top-level exit callback.
 *
 * @param root_menu Root menu pointer
 * @param menu_exit_cb Top-level exit callback
 * @param custom_menu_header Optional custom header
 */
static void initialize_menu_view_state(menu_t *root_menu, menu_exit_cb_t menu_exit_cb, const char *custom_menu_header)
{
    current_menu_pointer = root_menu;
    menu_1st_item = root_menu;
    menu_level = 0U;
    cursor_selection_menu_index[menu_level] = 0U;
    cursor_row_position[menu_level] = 0U;
    menu_top_level_exit_cb = menu_exit_cb;
    custom_header = custom_menu_header;

    update_screen_view();
}

/**
 * @brief Display appropriate menu header (main or submenu).
 */
static void display_menu_header(void)
{
    fill_header_with_dashes();

    if (current_menu_pointer->parent == NULL)
        display_main_menu_header();
    else
        display_sub_menu_header();
}

/**
 * @brief Displays the main menu header (top-level view).
 *
 * Centers the custom header if provided; otherwise, uses default column.
 * Sets menu_item_2_print to first menu item for rendering.
 */
static void display_main_menu_header(void)
{
    const char *header_str = default_header;
    uint8_t column = DEFAULT_MENU_HEADER_COLUMN;

    if (custom_header != NULL)
    {
        header_str = custom_header;
        const uint8_t header_length = (uint8_t)strlen(custom_header);

        /* Center custom header on the screen if it fits */
        if (menu_number_of_chars_per_line > header_length)
        {
            column = (menu_number_of_chars_per_line - header_length) / 2U;
        }
        else
        {
            /* Fallback to first column if header is longer than screen width */
            column = FIRST_COLUMN;
        }
    }

    /* Move cursor and print header */
    DISPLAY->cursor_position(FIRST_ROW, column);
    DISPLAY->print_string(header_str);

    /* Set pointer to first menu item for rendering */
    menu_item_2_print = menu_1st_item;
}

/**
 * @brief Display header for submenu.
 *
 * Centers parent menu name with padding and sets
 * menu_item_2_print to first child menu item.
 */
static void display_sub_menu_header(void)
{
    const char *parent_name = current_menu_pointer->parent->name;
    uint8_t header_len = (uint8_t)strlen(parent_name) + ADDITIONAL_SPACE_CHAR_QTY;
    uint8_t header_start;

    /* Center header on screen if it fits, otherwise start at first column */
    if (menu_number_of_chars_per_line > header_len)
    {
        header_start = (menu_number_of_chars_per_line - header_len) / 2U;
    }
    else
    {
        header_start = FIRST_COLUMN;
    }

    /* Move cursor and print header with padding */
    DISPLAY->cursor_position(FIRST_ROW, header_start);
    DISPLAY->print_char(' ');
    DISPLAY->print_string(parent_name);
    DISPLAY->print_char(' ');

    /* Set pointer to first child menu item for rendering */
    menu_item_2_print = current_menu_pointer->parent->child;
}

/**
 * @brief Fill header row with dash characters.
 */
static void fill_header_with_dashes(void)
{
    DISPLAY->cursor_position(FIRST_ROW, FIRST_COLUMN);
    for (uint8_t i = 0U; i < menu_number_of_chars_per_line; i++)
        DISPLAY->print_char('-');
}

/**
 * @brief Clear the menu view area on the screen.
 */
static void clear_current_menu_view_with_cursor(void)
{
    for (uint8_t i = MENU_VIEW_FIRST_ROW; i < menu_number_of_screen_lines; i++)
    {
        DISPLAY->cursor_position(i, FIRST_COLUMN);
        for (uint8_t j = 0U; j < menu_number_of_chars_per_line; j++)
            DISPLAY->print_char(' ');
    }
}

/**
 * @brief Adjust pointer to the first menu item to print.
 *
 * Calculates offset from cursor selection index to row position.
 */
static void update_menu_item_pointer_to_print(void)
{
    uint8_t offset = cursor_selection_menu_index[menu_level] - cursor_row_position[menu_level];
    for (uint8_t i = 0U; i < offset; i++)
    {
        if (menu_item_2_print == NULL)
            break;
        menu_item_2_print = menu_item_2_print->next;
    }
}

/**
 * @brief Render visible menu items with cursor.
 */
static void update_current_menu_view_with_cursor(void)
{
    for (uint8_t row = MENU_VIEW_FIRST_ROW; row < menu_number_of_screen_lines; row++)
    {
        display_cursor_marker_if_needed(row);

        if (menu_item_2_print == NULL)
        {
            // Null -> no more items to print on lcd 
            break;
        }

        display_menu_item_name(row, menu_item_2_print->name);
        menu_item_2_print = menu_item_2_print->next;
    }
}

/**
 * @brief Display '>' marker if current row is selected.
 *
 * @param row Screen row to draw cursor marker
 */
static void display_cursor_marker_if_needed(uint8_t row)
{
    DISPLAY->cursor_position(row, CURSOR_COLUMN_POSITION);
    if (row == (cursor_row_position[menu_level] + MENU_VIEW_FIRST_ROW))
        DISPLAY->print_char('>');
}

/**
 * @brief Display an error message at the given row.
 *
 * @param row Screen row to display error
 * @param msg Error message string
 */
// static void display_error_line(uint8_t row, const char *msg)
// {
//     DISPLAY->cursor_position(row, STRING_START_POSITION);
//     DISPLAY->print_string(msg);
// }

/**
 * @brief Display the name of a menu item at the given row.
 *
 * @param row Screen row to display the item
 * @param name Menu item name (fallback to "NO NAME" if NULL)
 */
static void display_menu_item_name(uint8_t row, const char *name)
{
    const char *text_to_print = name;
    if (text_to_print == NULL)
    {
        text_to_print = "NO NAME";
    }

    DISPLAY->cursor_position(row, STRING_START_POSITION);
    DISPLAY->print_string(text_to_print);
}

/** @} */ /* end of MenuLib group */
