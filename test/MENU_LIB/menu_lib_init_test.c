#include "unity/fixture/unity_fixture.h"
#include "menu_lib.h"
#include "mock_menu_implementation.h"
#include "menu_screen_driver_interface.h"
#include "mock_menu_screen_driver_interface.h"
#include <stddef.h>
#include <stdbool.h>

extern menu_t *menu_entry_point;
extern uint8_t menu_number_of_chars_per_line;
extern uint8_t menu_number_of_screen_lines;
extern bool menu_initialized;
extern const struct menu_screen_driver_interface_struct *DISPLAY;

// DISPLAY mock
extern const struct menu_screen_driver_interface_struct mock_menu_screen_driver_interface;

TEST_GROUP(menu_lib_init);

TEST_SETUP(menu_lib_init)
{
    menu_initialized = false;
    init_mock_screen_driver();
}
TEST_TEAR_DOWN(menu_lib_init)
{
}

TEST(menu_lib_init, WhenMenuInitThenMenuScreenSizeEqualToPassedConfigDataColumnCountAndRowCount)
{
    menu_init();
    TEST_ASSERT_EQUAL(20, menu_number_of_chars_per_line);
    TEST_ASSERT_EQUAL(4, menu_number_of_screen_lines);
}

TEST(menu_lib_init, WhenMenuInitThenMenuScreenDriverInterfaceisEqualToMockMenuScreenDriverInterface)
{
    menu_init();
    TEST_ASSERT_EQUAL(DISPLAY, &mock_menu_screen_driver_interface);
}

TEST(menu_lib_init, WhenMenuViewInitWithoutInitThenReturnNotInitialized)
{
    menu_initialized = false;
    menu_t dummy_menu = {0};
    menu_status_t status = menu_view_init(&dummy_menu, NULL, NULL);
    TEST_ASSERT_EQUAL(MENU_ERR_NOT_INITIALIZED, status);
}

TEST(menu_lib_init, WhenMenuViewInitWithNullRootMenuThenReturnNoMenu)
{
    menu_initialized = true;
    menu_status_t status = menu_view_init(NULL, NULL, NULL);
    TEST_ASSERT_EQUAL(MENU_ERR_NO_MENU, status);
}

TEST(menu_lib_init, WhenMenuViewInitWithTooDeepMenuThenReturnMenuDepthTooShallow)
{
    menu_initialized = true;
    static menu_t deep_menu[MAX_MENU_DEPTH + 1];
    for (int i = 0; i <= MAX_MENU_DEPTH; i++)
        deep_menu[i].child = (i < MAX_MENU_DEPTH) ? &deep_menu[i + 1] : NULL;

    menu_status_t status = menu_view_init(&deep_menu[0], NULL, NULL);
    TEST_ASSERT_EQUAL(MENU_ERR_MENU_TOO_DEEP, status);
}

TEST(menu_lib_init, WhenMenuViewInitWithValidMenuThenReturnOk)
{
    menu_initialized = true;
    menu_t valid_menu = {0};
    valid_menu.name = "Root";

    menu_status_t status = menu_view_init(&valid_menu, NULL, NULL);
    TEST_ASSERT_EQUAL(MENU_OK, status);
    TEST_ASSERT_EQUAL(&valid_menu, get_current_menu_position());
}

TEST(menu_lib_init, WhenMenuInitThenReturnOk)
{
    menu_status_t status = menu_init();
    TEST_ASSERT_EQUAL(MENU_OK, status);
    TEST_ASSERT_EQUAL(&mock_menu_screen_driver_interface, DISPLAY);
    TEST_ASSERT_EQUAL(DISPLAY->get_number_of_chars_per_line(), menu_number_of_chars_per_line);
    TEST_ASSERT_EQUAL(DISPLAY->get_number_of_screen_lines(), menu_number_of_screen_lines);
}

TEST(menu_lib_init, WhenInitWithValidDisplayThenReturnOk)
{
    menu_status_t status = menu_init();

    TEST_ASSERT_EQUAL(MENU_OK, status);
    TEST_ASSERT_EQUAL(&mock_menu_screen_driver_interface, DISPLAY);
    TEST_ASSERT_EQUAL(DISPLAY->get_number_of_chars_per_line(), menu_number_of_chars_per_line);
    TEST_ASSERT_EQUAL(DISPLAY->get_number_of_screen_lines(), menu_number_of_screen_lines);
    TEST_ASSERT_TRUE(menu_initialized);
}

TEST(menu_lib_init, WhenInitWithNullDisplayThenReturnNoDisplayInterface)
{
    // given
    deinit_mock_screen_driver(); // mock zwraca NULL

    // when
    menu_status_t status = menu_init();

    // then
    TEST_ASSERT_EQUAL(MENU_ERR_NO_DISPLAY_INTERFACE, status);
    TEST_ASSERT_FALSE(menu_initialized);
}

TEST(menu_lib_init, WhenInitWithIncompleteDisplayThenReturnIncompleteInterface)
{
    // given

    init_mock_incomplete_screen_driver();

    // when
    menu_status_t status = menu_init();

    // then
    TEST_ASSERT_EQUAL(MENU_ERR_INCOMPLETE_INTERFACE, status);
    TEST_ASSERT_FALSE(menu_initialized);

    // przywrócenie poprawnego mocka
    init_mock_screen_driver();
}
