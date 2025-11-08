add_executable(
    string_conversation_traits_tests
    has_ostream_operator_tests.cpp
    has_to_string_conversion_operator_tests.cpp
    is_constructible_tests.cpp
    is_convertible_to_base_tests.cpp
    is_to_string_compatible_tests.cpp
    )

target_link_libraries(string_conversation_traits_tests
  PRIVATE
    string_conversation_traits
    gtest_main
  )

target_include_directories(string_conversation_traits_tests
  PRIVATE
    ${GTEST_INCLUDE_DIRS}
  )

# automatic discovery of "string_conversation_traits" tests
gtest_discover_tests(string_conversation_traits_tests
PROPERTIES
    LABELS "string_conversation_traits"                   
    DISCOVERY_TIMEOUT 240           # how long to wait (in seconds) before crashing
)