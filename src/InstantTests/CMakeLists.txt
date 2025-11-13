add_executable(instant_tests EXCLUDE_FROM_ALL
    instant_tests.cpp
    )

target_link_libraries(instant_tests
  PRIVATE
    universal_converter_to_string
  )

# if clang tidy was found enable it for the target
if (CUSTOM_CLANG_TIDY)
  set_target_properties(instant_tests PROPERTIES
    CXX_CLANG_TIDY
    "$<$<CONFIG:StaticAnalysis>:${CLANG_TIDY_COMMAND}>"
  )
endif()

if (ENABLE_INCLUDE_WHAT_YOU_USE)
  set_target_properties(instant_tests PROPERTIES 
    CXX_INCLUDE_WHAT_YOU_USE
    "$<$<CONFIG:StaticAnalysis>:${INCLUDE_WHAT_YOU_USE_COMMAND}>"
  )
endif()