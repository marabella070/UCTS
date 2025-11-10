add_executable(demo_program EXCLUDE_FROM_ALL
    demo_program.cpp
    )

target_link_libraries(demo_program
  PRIVATE
    universal_converter_to_string
  )

