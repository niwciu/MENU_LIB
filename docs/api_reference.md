# 📘 MENU_LIB — API Reference

This document provides a concise technical reference for the public API of the **MENU_LIB** library.  
It includes all exported types, functions, and callback definitions for integrating and controlling hierarchical menus in embedded systems.

---

## 📖 Overview

The library provides:
- Initialization and validation of the menu engine.  
- Hierarchical navigation (next, previous, enter, escape).  
- Screen rendering through an abstract display driver interface.  
- Access to the currently selected menu item.  

All functions and types are defined across the following headers:
- `menu_lib.h`
- `menu_lib_type.h`
- `menu_screen_driver_interface.h`

---

## 🧩 Enumerations

### `menu_status_t`
Defined in **`menu_lib_type.h`**  
Return codes used across all MENU_LIB functions.

```c
typedef enum
{
    MENU_OK = 0,                         // Operation successful
    MENU_ERR_NO_DISPLAY_INTERFACE = 1,   // Display driver interface not initialized or missing
    MENU_ERR_INCOMPLETE_INTERFACE = 2,   // Display driver missing required functions
    MENU_ERR_NOT_INITIALIZED = 3,        // Menu system not initialized (menu_init() not called)
    MENU_ERR_NO_MENU = 4,                // Root menu pointer is NULL
    MENU_ERR_MENU_TOO_DEEP = 5,          // Menu depth exceeds MAX_MENU_DEPTH
    MENU_ERR_NULL_MENU_ITEM = 6          // NULL menu item encountered during view update
} menu_status_t;
```

---

## 🧱 Structures

### `menu_t`
Represents a single menu item within the hierarchical tree.

```c
typedef struct menu_t
{
    const char *name;         // Displayed name of the menu item
    struct menu_t *next;      // Pointer to the next item on the same level
    struct menu_t *prev;      // Pointer to the previous item on the same level
    struct menu_t *child;     // Pointer to the submenu (child menu)
    struct menu_t *parent;    // Pointer to the parent menu
    void (*callback)(void);   // Function executed when the item has no child (leaf node)
} menu_t;
```

**Notes:**
- Each menu level forms a doubly linked list.
- The `callback` is executed only if the `child` pointer is `NULL`.

---

### `menu_screen_driver_interface_struct`
Abstraction layer between the menu engine and hardware-specific display.

```c
struct menu_screen_driver_interface_struct
{
    void (*screen_init)(void);
    uint8_t (*get_number_of_screen_lines)(void);
    uint8_t (*get_number_of_chars_per_line)(void);
    void (*clr_scr)(void);
    void (*cursor_position)(uint8_t row, uint8_t column);
    void (*print_string)(const char *string);
    void (*print_char)(const char character);
};
```

**Usage:**
- All function pointers must be implemented in the user’s display driver.
- The structure is obtained internally via `get_menu_display_driver_interface()`.

---

## 🔁 Callback Types

### `menu_exit_cb_t`
Callback function type executed when the top-level menu is exited.

```c
typedef void (*menu_exit_cb_t)(void);
```

**Example:**
```c
void on_menu_exit(void) {
    // Return to main screen or perform cleanup
}
```

---

## ⚙️ Core API Functions

### `menu_status_t menu_init(void)`
Initializes the menu engine and validates the display driver interface.  
Must be called before any other menu-related function.

**Return values:**
| Code | Meaning |
|------|----------|
| `MENU_OK` | Initialization successful |
| `MENU_ERR_NO_DISPLAY_INTERFACE` | Display driver interface not found (`DISPLAY == NULL`) |
| `MENU_ERR_INCOMPLETE_INTERFACE` | One or more required driver functions missing |

---

### `menu_status_t menu_view_init(menu_t *root_menu, menu_exit_cb_t menu_exit_cb, const char *custom_menu_header)`
Initializes and displays a menu view starting from the given root menu.

**Parameters:**
- `root_menu` — pointer to the root of the menu hierarchy.  
- `menu_exit_cb` — callback executed when exiting the top-level menu.  
- `custom_menu_header` — optional string for a custom header (or `NULL` for default).  

**Return values:**
| Code | Meaning |
|------|----------|
| `MENU_OK` | View initialized successfully |
| `MENU_ERR_NOT_INITIALIZED` | Menu system not initialized (menu_init() not called) |
| `MENU_ERR_NO_MENU` | Root menu pointer is `NULL` |
| `MENU_ERR_MENU_TOO_DEEP` | Menu hierarchy exceeds `MAX_MENU_DEPTH` |

---

### `void menu_next(void)`
Moves the cursor to the next menu item on the same level.  
If there is no next item, no action is performed.

---

### `void menu_prev(void)`
Moves the cursor to the previous menu item on the same level.  
If there is no previous item, no action is performed.

---

### `void menu_enter(void)`
Executes the selected menu item action.

**Behavior:**
- If the selected item has a `child`, enters its submenu.  
- If the item **has no child but defines a `callback`**, that callback is executed.  
- If both are `NULL`, no action is taken.

---

### `void menu_esc(void)`
Exits the current submenu or top-level menu.

**Behavior:**
- If the current item has a `parent`, moves one level up.  
- If the current menu is at the top level, executes the registered `menu_exit_cb_t` callback.

---

### `void update_screen_view(void)`
Refreshes the current screen view.

**Behavior:**
- Redraws the menu header and visible items.  
- Updates the cursor position.  
- Adjusts internal pointers to reflect the current state.

---

### `menu_t *get_current_menu_position(void)`
Returns a pointer to the currently selected menu item.

**Returns:**  
Pointer to the `menu_t` structure representing the current selection.

---

## 🧠 Display Driver Interface Access

### `const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void)`
Returns a constant pointer to the active display driver interface.  
Used internally during initialization and rendering.

---

## 🧩 Constants

| Constant | Description |
|-----------|--------------|
| `MAX_MENU_DEPTH` | Maximum allowed menu hierarchy depth (defined in `menu.h`). |
| `MENU_OK` | Successful operation status. |
| `FIRST_ROW`, `FIRST_COLUMN` | Screen coordinate indices used internally. |

---

© 2025 Niwciu — MENU_LIB  
*Technical reference for developers integrating the MENU_LIB engine.*