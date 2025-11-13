# This module provides commands to populate content at configure time.
include(FetchContent)

FetchContent_Declare(gtest

  # 52eb8108c5bdec04579160ae17225d66034bd723 - последний верифицированный коммит версии 1.17.0, 
  #                                             на момент написания этого кода.
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.tar.gz
)

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

# This module provides commands to help use the Google Test infrastructure.
include(GoogleTest)

add_subdirectory(UniversalConverterToStringTraitsTests)

add_subdirectory(UniversalConverterToStringTests)
