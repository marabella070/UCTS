add_executable(type_requirements_analyzer EXCLUDE_FROM_ALL
    type_requirements_analyzer.cpp
    )

target_link_libraries(type_requirements_analyzer
  PRIVATE
    string_conversation_traits
  )

