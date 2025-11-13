add_executable(
    universal_converter_to_string_traits_tests
    has_ostream_operator_tests.cpp
    has_to_string_conversion_operator_tests.cpp
    is_constructible_tests.cpp
    is_convertible_to_base_tests.cpp
    is_convertible_to_string_tests.cpp
    is_to_string_compatible_tests.cpp
    )

target_link_libraries(universal_converter_to_string_traits_tests
  PRIVATE
    universal_converter_to_string
    gtest_main
  )

target_include_directories(universal_converter_to_string_traits_tests
  PRIVATE
    ${GTEST_INCLUDE_DIRS}
  )

# if clang tidy was found enable it for the target
if (ENABLE_CLANG_TIDY)
  set_target_properties(universal_converter_to_string_traits_tests PROPERTIES
    CXX_CLANG_TIDY
    "$<$<CONFIG:StaticAnalysis>:${CLANG_TIDY_COMMAND}>"
  )
endif()

if (ENABLE_INCLUDE_WHAT_YOU_USE)
  set_target_properties(universal_converter_to_string_traits_tests PROPERTIES 
    CXX_INCLUDE_WHAT_YOU_USE
    "$<$<CONFIG:StaticAnalysis>:${INCLUDE_WHAT_YOU_USE_COMMAND}>"
  )
endif()

# automatic discovery of "universal_converter_to_string_traits" tests
gtest_discover_tests(universal_converter_to_string_traits_tests
PROPERTIES
    LABELS "universal_converter_to_string_traits"                   
    DISCOVERY_TIMEOUT 240           # how long to wait (in seconds) before crashing
)