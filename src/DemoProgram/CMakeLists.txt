add_executable(demo_program
    demo_program.cpp
    )

target_link_libraries(demo_program
  PRIVATE
    universal_converter_to_string
  )

