add_library(universal_converter_to_string)

target_sources(universal_converter_to_string
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/universal_converter_to_string_traits.h
    ${CMAKE_CURRENT_LIST_DIR}/universal_converter_to_string.h
    ${CMAKE_CURRENT_LIST_DIR}/universal_converter_to_string.cpp
  )

target_include_directories(universal_converter_to_string
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# if clang tidy was found enable it for the target
if (CUSTOM_CLANG_TIDY)
  set_target_properties(universal_converter_to_string PROPERTIES
    CXX_CLANG_TIDY
    "$<$<CONFIG:StaticAnalysis>:${CLANG_TIDY_COMMAND}>"
  )
endif()

if (ENABLE_INCLUDE_WHAT_YOU_USE)
  set_target_properties(universal_converter_to_string PROPERTIES 
    CXX_INCLUDE_WHAT_YOU_USE
    "$<$<CONFIG:StaticAnalysis>:${INCLUDE_WHAT_YOU_USE_COMMAND}>"
  )
endif()

# We use this to get code coverage
if(CODE_COVERAGE_ENABLED)

  # Flags are only valid with the GNU compiler and on Linux
  # Other compilers and platforms may require alternative approaches
  if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

    target_compile_options(universal_converter_to_string
      PUBLIC
        "$<$<CONFIG:Coverage>:--coverage>"
      )

    # Связать с libgcov, создать .gcda
    target_link_options(universal_converter_to_string
      INTERFACE
        "$<$<CONFIG:Coverage>:--coverage>"
      )

  endif()

endif()
