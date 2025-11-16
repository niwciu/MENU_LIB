![menu_lib_header](https://github.com/user-attachments/assets/35244d64-4b3d-4c9c-88fb-4e6d756bbbb4)
# 🧩 MENU_LIB — Hierarchical Menu Library for Embedded Systems
**MENU_LIB** is a lightweight, portable library for building hierarchical, text-based menu systems on embedded platforms.
It separates **menu logic**, **display rendering**, and **menu data structures**, enabling flexible use across LCD, OLED, or UART-based interfaces.

---

## 🚀 Features

* 🧭 **Hierarchical Menu Navigation** — supports multi-level submenus and callbacks
* 🧩 **Hardware Independence** — compatible with any display driver implementing the screen interface
* 🧠 **Static Memory Model** — all menus defined at compile time (no dynamic allocation)
* ⚙️ **Customizable Rendering** — configurable headers, cursor positions, and line count
* 🔗 **Callback Integration** — execute user-defined functions directly from menu items
* 🧱 **Error-Safe Architecture** — validation for display drivers and menu depth
* 💡 **Designed for Embedded Targets** — minimal RAM and code footprint
* 🗂️ **Multiple Independent Menus** — architecture allows defining and switching between multiple menus (e.g., different device modes) without changing core logic
* ✍️ **Dynamic Labels Support** — item labels can be generated at runtime (e.g., values, states) while keeping the static structure of the tree

---

## 🧩 Architecture Overview

For an in-depth explanation of internal structure, data flow, and design principles, see the
👉 **[Architecture Overview](https://niwciu.github.io/MENU_LIB/architecture)** document.

That document covers:

* The 4-layer modular architecture
* Internal data structures (`menu_t`, `menu_status_t`)
* Rendering and navigation logic
* Display driver abstraction layer
* Error handling flow and design principles

---

## ⚙️ Getting Started

For detailed instructions on how to set up and use the library — including display driver configuration, menu definition, and initialization steps —
please refer to:

* 👉 [Getting Started Guide](https://niwciu.github.io/MENU_LIB/getting_started)
* 👉 [Menu Generator Tool](https://niwciu.github.io/MENU_LIB/menu_generator) — optional web-based tool for visually designing menus and generating compatible `menu.c` / `menu.h` files

---

## 🧩 Examples

Ready-to-run examples can be found in the [examples/](https://github.com/niwciu/MENU_LIB/tree/main/examples) directory.
Each example demonstrates a different use case (LCD display, UART terminal, FreeRTOS integration, etc.).

More details in 👉 [Examples Overview](https://niwciu.github.io/MENU_LIB/examples)

---

## 🧪 Reports and Metrics

The **MENU_LIB** project includes automated **CI pipelines** (GitHub Actions) that perform continuous checks and generate reports.

### ✅ CI Checks

* `cppcheck` — static code analysis
* `lizard` — code complexity check
* `gcovr` — coverage data collection
* Build verification
* Unit tests execution
* `clang-format` — formatting consistency check

Results of all checks are available in the **Actions** tab of the repository.

### 📊 Generated Reports

After successful build and test runs, the following reports are published to the project page:

* **CCM Report** — code complexity metrics
* **GCOVR Coverage Report** — unit test coverage summary
* **Doxygen Documentation** — automatically generated API reference

📄 See also: [Reports](https://niwciu.github.io/MENU_LIB/reports)

---

## 📘 API Reference

The complete API documentation is generated automatically with **Doxygen**
and published on the project page:

👉 [Online Documentation](https://niwciu.github.io/MENU_LIB/)

An additional API reference is also available in Markdown format:

👉 [API Reference (Markdown)](https://niwciu.github.io/MENU_LIB/api_reference)

---

## 👨‍💻 Contributing

Contributions, ideas, and improvements are welcome!
Please read the [CONTRIBUTING](https://niwciu.github.io/MENU_LIB/CONTRIBUTING) guide before submitting pull requests.
It includes:

* Build & test instructions
* Code style and formatting
* Adding new menu features or drivers
* Running analysis tools (cppcheck, ccm, coverage)

---

## 📄 License

This project is released under the **MIT License**.
See the [LICENSE](https://github.com/niwciu/MENU_LIB/blob/main/LICENSE) file for details.

---

© 2025 Niwciu — MENU_LIB
*Embedded menu system for modular, human-friendly interfaces.*
