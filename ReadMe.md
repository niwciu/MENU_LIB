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
👉 **[Architecture Overview](docs/architecture.md)** document.

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

* 👉 [Getting Started Guide](docs/getting_started.md)
* 👉 [Menu Generator Tool](docs/menu_generator.md) — optional web-based tool for visually designing menus and generating compatible `menu.c` / `menu.h` files

---

## 🧩 Examples

Ready-to-run examples can be found in the [examples/](examples/) directory.
Each example demonstrates a different use case (LCD display, UART terminal, FreeRTOS integration, etc.).

More details in 👉 [Examples Overview](docs/examples.md)

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

📄 See also: [Reports](docs/reports.md)

---

## 📘 API Reference

The complete API documentation is generated automatically with **Doxygen**
and published on the project page:

👉 [Online Documentation](https://niwciu.github.io/MENU_LIB/)

An additional API reference is also available in Markdown format:

👉 [API Reference (Markdown)](docs/api_reference.md)

---

## 👨‍💻 Contributing

Contributions, ideas, and improvements are welcome!
Please read the [CONTRIBUTING.md](docs/CONTRIBUTING.md) guide before submitting pull requests.
It includes:

* Build & test instructions
* Code style and formatting
* Adding new menu features or drivers
* Running analysis tools (cppcheck, ccm, coverage)

---

## 📄 License

This project is released under the **MIT License**.
See the [LICENSE](LICENSE) file for details.

---

© 2025 Niwciu — MENU_LIB
*Embedded menu system for modular, human-friendly interfaces.*
