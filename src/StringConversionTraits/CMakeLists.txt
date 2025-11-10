add_library(string_conversation_traits INTERFACE)

target_include_directories(string_conversation_traits
  INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
  )

# # We use this to get code coverage
# # Flags are only valid with the GNU compiler and on Linux
# if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

#   target_compile_options(string_conversation_traits
#     PUBLIC
#       "--coverage"
#     )

#   target_link_options(string_conversation_traits
#     INTERFACE
#       "--coverage"
#     )

# endif()
