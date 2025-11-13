cmake_minimum_required(VERSION 3.20)
# project(menu_lib C)

add_library(menu_lib STATIC
  ../../../../lib/MENU_LIB/menu_lib.c    
)

set_target_properties(menu_lib PROPERTIES 
  OUTPUT_NAME "menu_lib"
  PREFIX ""
)

target_include_directories(menu_lib PUBLIC 
  ../../../../lib/MENU_LIB    
  ../../src/ui              # obecny katalog źródeł
)
