# 🤝 Contributing to MENU_LIB

Thank you for your interest in contributing to **MENU_LIB**!  
This guide explains how to fork the project, set up a local environment, run the CI workflow locally, and submit pull requests.

---

## 🧩 Contribution Workflow

### 1️⃣ Fork the repository

Create your own fork on GitHub:

> [https://github.com/niwciu/MENU_LIB](https://github.com/niwciu/MENU_LIB)

Clone it locally:

```bash
git clone https://github.com/<your-username>/MENU_LIB.git
cd MENU_LIB
```

---

## 🧰 System Requirements

To run MENU_LIB CI locally, make sure the following tools are installed and available in your system PATH:

| Tool                   | Purpose                | Min Version |
| ---------------------- | ---------------------- | ----------- |
| **CMake**              | Build configuration    | 3.16+       |
| **Make / Ninja**       | Build execution        | —           |
| **gcc / clang / gcov** | Compilation & coverage | —           |
| **cppcheck**           | Static analysis        | 2.10+       |
| **clang-format**       | Code style enforcement | 12+         |
| **python3**            | Script execution       | 3.8+        |

> 💡 On Ubuntu/Debian you can install most dependencies with:  
> `sudo apt install cmake make gcc g++ cppcheck clang-format python3 python3-venv`

Alternatively, you can use the ready-to-run Docker image  
👉 `niwciu/stm32_dev_container`  
which contains all required tools preinstalled — no `venv` setup is needed.

---

## ⚙️ Python Environment Setup (venv)

Python-based tools such as **gcovr** (coverage) and **lizard** (complexity metrics) are installed via a virtual environment.

Create and initialize it:

```bash
cd test/_config_scripts/venv_setup
python3 venv_setup.py
```

This will:

* verify that pip is available,
* create a local virtual environment in `../.venv`,
* install dependencies from `requirements.txt`.

Then **activate** it:

```bash
source ../.venv/bin/activate        # Linux/macOS
../.venv/Scripts/activate.bat       # Windows
```

> ⚠️ The CI workflow (`CI.py`) assumes the virtual environment is already active.

---

## 🧪 Running Local CI Workflow

Once the environment is active, you can run all CI checks locally:

```bash
cd test/_config_scripts/CI
python3 CI.py
```

This script:

* builds and tests all modules,
* performs **static analysis** (`cppcheck`),
* performs **complexity analysis** (`lizard`, `ccm`),
* generates **coverage reports** (`gcovr`),
* checks formatting (`clang-format`),
* produces HTML reports under `reports/`,
* opens reports automatically in your browser.

Configuration is defined in:
```
test/_config_scripts/CI/config.yaml
```

---

### 🔧 Manual Build and Target Execution

If you prefer to build and execute targets manually, navigate to the unit test directory:

```bash
cd test/MENU_LIB
```

#### Build with Unix Makefiles
```bash
cmake -S./ -B out -G"Unix Makefiles"
cd out
make all # optional with -j flag passing core numbers to speed up, e.g. -j12
```

#### Build with Ninja
```bash
cmake -S./ -B out -G"Ninja"
cd out
ninja
```

#### Available CMake Targets
```bash
make run          # Run unit tests
make cppcheck     # Static analysis
make ccm          # Code complexity metrics in console
make ccmr         # Complexity report (HTML)
make ccc          # Coverage check (gcovr summary in console)
make ccr          # Coverage report (HTML)
make format       # Apply formatting (source)
make format_test  # Apply formatting (test code)
```

All reports are generated in the `reports/` subfolders.

---

## ☁️ Alternative: GitHub Actions

All CI checks are also executed automatically by **GitHub Actions** when you open a pull request or push to a branch.

You can monitor results directly in the **Actions** tab of the repository.  
The generated reports and Doxygen documentation are published to the project’s GitHub Pages.

---

## 🧠 Coding Style

Follow these conventions to maintain code consistency:

* **Language standard:** C99  
* **Indentation:** 4 spaces, no tabs  
* **Braces:** K&R style  
* **Max line length:** 100 characters  
* **Function naming:** `snake_case` (e.g. `menu_update_view()`)  
* **Constants:** Uppercase with underscores (`MAX_MENU_DEPTH`)  
* **Enums and structs:** Use explicit `typedef` names  
* **Comments:** Doxygen-compatible documentation blocks

Example:
```c
/**
 * @brief Refresh the current menu screen.
 *
 * Updates header and menu item visibility.
 */
void update_screen_view(void);
```

---

## 🧩 Adding New Features

### 🧩 Adding a New Display Driver

New display drivers are typically implemented **outside** the library, within the application layer or example projects.  
If a reference driver is created for a specific hardware platform, it can be added under `examples/driver_interface/`.

Naming convention for such files should clearly indicate their target platform or controller, e.g.:  
`niwciu_LCD_HD44780_display_driver.c`

Doxygen comments for the driver should include a brief description of the external display library used and link to its source.

---

#### Example driver interface

Each driver must implement the full **display interface contract** defined in  
`menu_screen_driver_interface_struct`:

```c
void screen_init(void);
void clr_scr(void);
void cursor_position(uint8_t row, uint8_t col);
void print_string(const char *str);
void print_char(const char ch);
uint8_t get_number_of_screen_lines(void);
uint8_t get_number_of_chars_per_line(void);
```

In addition, the driver must expose a function returning a pointer to its interface structure:

```c
const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void);
```

This function allows the MENU_LIB engine to access the driver’s implementation through the common interface.

---

> ⚠️ The driver must not contain `NULL` entries in its structure.  
> Validation will be added in future safety-critical releases of the library.

Note: Drivers are not unit-tested within MENU_LIB — in tests, they are mocked.  
To verify integration, use the example project that includes full hardware configuration in the `HW/` directory.

---

### Extending the Menu Engine

If adding new functionality to the core (`menu_lib.c`):

* Ensure no dynamic allocation is introduced.  
* Keep full backward compatibility of the API.  
* Add unit tests for new behavior.  
* Update `docs/api_reference.md` accordingly.

---

## 🧩 Documentation

Before committing, make sure your new or modified functions include proper Doxygen comments.  
You can verify the generated documentation locally.

### Generate Doxygen Docs
```bash
cd docs/doxygen
doxygen Doxyfile
```

Output:
```
docs/html/index.html
```

Documentation and reports are automatically rebuilt and published on every successful CI run in GitHub Actions.

---

## 🧩 Reporting Issues

Please report bugs or feature requests in the  
👉 [GitHub Issues](https://github.com/niwciu/MENU_LIB/issues)

Include:

* Library version or commit hash  
* Platform / compiler info  
* Steps to reproduce  
* Expected and actual results

---

© 2025 Niwciu — MENU_LIB  
*Contribute with care. Keep it simple. Keep it clean.*