# 🧩 MENU Generator Tool

## 📘 Overview
The **MENU Generator Tool** is a web-based application that allows you to visually design hierarchical menus for the **MENU_LIB** library.  
It generates ready-to-use `menu.c` and `menu.h` files compatible with the `menu_t` structure.

🔗 **Live tool:** [https://niwciu.github.io/LCD_MENU_GENERATOR_APP/](https://niwciu.github.io/LCD_MENU_GENERATOR_APP/)  
💻 **Source code:** [GitHub — LCD_MENU_GENERATOR_APP](https://github.com/niwciu/LCD_MENU_GENERATOR_APP)

---

## ⚙️ Usage Workflow

1. **Open the tool**  
   Go to the web application link above.

2. **Add your first menu item**  
   Click the **“+” button** next to the **MENU** label to create the first item.  
   Enter the item name — it must not exceed `(number of display columns - 1)` characters.

3. **Add more items**  
   - To add a new item on the **same level**, click the **“+” button** next to the menu title again.  
   - To create a **submenu**, click the **“+” next to an existing item**.

4. **Reorder items**  
   Use the **up/down arrow buttons** to move items within the **same menu level**.  
   Moving items between different hierarchy levels is **not supported** — each item can only be reordered inside its current parent menu.


5. **Delete items**  
   Click the **trash icon** to remove an item together with all its sub-items.

6. **Save your structure**  
   Use the **green Save icon** (💾) in the top bar to export your menu as a `.json` file.

7. **Load an existing menu**  
   Use the **Open icon** (📂) to load a previously saved `.json` structure and edit it.

8. **Generate source code**  
   Click the **green icon with a pencil and page** ✏️📄 to generate C source code.  
   Two files will be generated:
   - `menu.c`  
   - `menu.h`

9. **Enable callback generation (optional)**  
   To include function stubs for callbacks, enable the checkbox  
   **“Enable menu items execute callback generation”**.  
   Callback functions are generated **only if a name is entered** for that menu item.

10. **Export generated code**  
    - You can **copy** the generated code directly from the preview.  
    - Or **download** ready `.c` and `.h` files and copy them into your project.

---

## 🧠 Notes

- The generator **automatically calculates menu depth** and displays the current maximum depth in the UI (`MAX MENU DEPTH: n`).  
- It prevents creating structures that exceed the limits defined by `MAX_MENU_DEPTH`.  
- The output files are immediately ready to be compiled together with **MENU_LIB**.  
- Callback stubs are only added when a function name is provided in the input field.

---

## 📘 Related Documentation
- [Getting Started Guide](https://niwciu.github.io/MENU_LIB/getting_started.md)  
- [Architecture Overview](https://niwciu.github.io/MENU_LIB/architecture.md)  
- [API Reference](https://niwciu.github.io/MENU_LIB/api_reference.md)

---

© 2025 Niwciu — MENU_LIB  
*Web-based generator for creating menu structures compatible with MENU_LIB.*
