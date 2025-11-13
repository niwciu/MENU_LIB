cmake_minimum_required(VERSION 3.20)

add_library(pushbutton_lib STATIC
  ./pushbutton.c    
)

# set_target_properties(pushbutton_lib PROPERTIES OUTPUT_NAME "pushbutton_lib")
set_target_properties(pushbutton_lib PROPERTIES 
  OUTPUT_NAME "pushbutton_lib"
  PREFIX ""
  )

target_include_directories(pushbutton_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
