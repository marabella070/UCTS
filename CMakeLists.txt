cmake_minimum_required(VERSION 3.13)

# Used to explicitly specify how timestamps should be handled. 
# The OLD behavior for this policy is to restore the timestamps from the archive. 
# The NEW behavior sets the timestamps of extracted contents to the time of extraction.
if (POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

project(universal_converter_to_string VERSION 1.0.0 LANGUAGES CXX)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if(CMAKE_CONFIGURATION_TYPES)
  if("MinSizeRel" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(REMOVE_ITEM CMAKE_CONFIGURATION_TYPES "MinSizeRel")
  endif()

  if("Debug" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(REMOVE_ITEM CMAKE_CONFIGURATION_TYPES "Debug")
  endif()

  if(NOT "DebugWithWarnings" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES "DebugWithWarnings")
  endif()

  if(NOT "DebugWithSanitizers" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES "DebugWithSanitizers")
  endif()

  if(NOT "StaticAnalysis" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES "StaticAnalysis")
  endif()

  if(NOT "Coverage" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES "Coverage")
  endif()
else()
  set(allowableBuildTypes Release RelWithDebInfo DebugWithWarnings DebugWithSanitizers StaticAnalysis Coverage)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${allowableBuildTypes})

  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)  # DebugWithWarnings by default
  elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

# More warnings are always good.
set(CMAKE_C_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -pedantic" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_DEBUGWITHWARNINGS
    "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)

# Используется для инициализации свойства DEBUGWITHWARNINGS_POSTFIX каждой целевой библиотеки, 
# значение которого добавляется к имени файла такой цели при сборке для указанной конфигурации.
set(CMAKE_DEBUGWITHWARNINGS_POSTFIX _dw)

# Helps to detect memory leaks and undefined behavior in runtime.
set(CMAKE_C_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_DEBUGWITHSANITIZERS
    "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)

set(CMAKE_DEBUGWITHSANITIZERS_POSTFIX _ds)


# Debugging information helps clang-tidy work more efficiently.
set(CMAKE_C_FLAGS_STATICANALYSIS
    "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_STATICANALYSIS
    "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_STATICANALYSIS
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_STATICANALYSIS
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_STATICANALYSIS
    "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_STATICANALYSIS
    "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)

set(CMAKE_STATICANALYSIS _st_analysis)


# Сохраняем статические константы и inline-функции в объектных файлах
# для корректного анализа покрытия, даже если они не используются явно.
set(CMAKE_C_FLAGS_COVERAGE
    "${CMAKE_C_FLAGS_DEBUG} -fkeep-inline-functions -fkeep-static-consts" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_COVERAGE
    "${CMAKE_CXX_FLAGS_DEBUG} -fkeep-inline-functions -fkeep-static-consts" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_COVERAGE
    "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_COVERAGE
    "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)

set(CMAKE_COVERAGE_POSTFIX _cov)


# if clang-tidy is not already set, it is searched for here and configuring it for static analysis
if(NOT CMAKE_CXX_CLANG_TIDY)
  find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)

  if(NOT CLANG_TIDY_EXECUTABLE)
    message(WARNING "Static analysis with clang-tidy is required, but clang-tidy is not found. Static analysis will be disabled.")
    option(CUSTOM_CLANG_TIDY "Custom CLANG_TIDY" OFF)
  else()
    option(CUSTOM_CLANG_TIDY "Custom CLANG_TIDY" ON)
      
    list(APPEND CLANG_TIDY_COMMAND "${CLANG_TIDY_EXECUTABLE}"
    "-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
  endif()

endif()

# we cannot analyse results without gcov
find_program(GCOV_PATH gcov)
if(NOT GCOV_PATH)
  message(WARNING "Code coverage analysis requires gcov, but gcov was not found. Coverage analysis will be skipped.")
  set(CODE_COVERAGE_ENABLED OFF)
else()
  set(CODE_COVERAGE_ENABLED ON)
endif()


# if the iwyu program is found it is configured
find_program(INCLUDE_WHAT_YOU_USE_EXECUTABLE NAMES include-what-you-use iwyu)

if(NOT INCLUDE_WHAT_YOU_USE_EXECUTABLE)
  option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable iwyu" OFF)
  message(WARNING "include-what-you-use was not found - header include analysis will be skipped")

else()
  option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable iwyu" ON)
    
  list(APPEND INCLUDE_WHAT_YOU_USE_COMMAND "${INCLUDE_WHAT_YOU_USE_EXECUTABLE}")
endif()


add_subdirectory(src)

enable_testing()

add_subdirectory(tests)

