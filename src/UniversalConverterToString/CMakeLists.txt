add_library(universal_converter_to_string)

target_sources(universal_converter_to_string
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/universal_converter_to_string.h
    ${CMAKE_CURRENT_LIST_DIR}/universal_converter_to_string.cpp
    ${CMAKE_CURRENT_LIST_DIR}/is_convertible_to_string.h
  )

target_include_directories(universal_converter_to_string
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(universal_converter_to_string
  PUBLIC
    string_conversation_traits
  )

# # We use this to get code coverage
# # Flags are only valid with the GNU compiler and on Linux
# if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

#   target_compile_options(universal_converter_to_string
#     PUBLIC
#       "--coverage"
#     )

#   target_link_options(universal_converter_to_string
#     INTERFACE
#       "--coverage"
#     )

# endif()