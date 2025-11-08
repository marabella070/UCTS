add_library(universal_converter_to_string INTERFACE)

target_link_libraries(universal_converter_to_string
  INTERFACE
    string_conversation_traits
  )

target_include_directories(universal_converter_to_string
  INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
  )

