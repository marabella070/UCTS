add_executable(
    universal_converter_to_string_tests
    is_convertible_to_string_tests.cpp
    universal_converter_to_string_tests.cpp
    )

target_include_directories(universal_converter_to_string_tests
  PRIVATE
    ${GTEST_INCLUDE_DIRS}
  )

target_link_libraries(universal_converter_to_string_tests
  PRIVATE
    universal_converter_to_string
    gtest_main
  )

# automatic discovery of "universal_converter_to_string" tests
gtest_discover_tests(universal_converter_to_string_tests
PROPERTIES
    LABELS "universal_converter_to_string"                   
    DISCOVERY_TIMEOUT 240           # how long to wait (in seconds) before crashing
)