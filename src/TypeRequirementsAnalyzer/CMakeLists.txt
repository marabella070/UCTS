add_executable(type_requirements_analyzer
    type_requirements_analyzer.cpp
    )

target_link_libraries(type_requirements_analyzer
  PRIVATE
    string_conversation_traits
  )

