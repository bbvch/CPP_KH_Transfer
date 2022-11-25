cmake_minimum_required(VERSION 3.12)
project("CPP_KH_TRANSFER"
        VERSION 1.0.0
        DESCRIPTION "C++ source files for the CPP KH-Transfer from bbv")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message("Compiler is: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0.1")
    message(
      WARNING "Insufficient g++ version - use 7.0.1 to compile all examples")
  elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10.0.0")
    set(ENABLE_CPP20_FEATURES TRUE)
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "^[cC]lang.*")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
    message(
      WARNING
        "Insufficient clang version - use 5.0.0 or above to compile all examples"
      )
  elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8.0.0")
    set(ENABLE_CPP20_FEATURES TRUE)
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^AppleClang.*")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10.0")
    message(
      WARNING
        "Insufficient AppleClang version - use 10.0 or above to compile all examples"
      )

  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "${MSVC_COMPILER_NAME}")
  message(WARNING "Insufficient msvc version ${CMAKE_CXX_COMPILER_VERSION}")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.16")
    message(
      WARNING
        "Insufficient MSCV version - use 16.16 or above to compile all examples"
      )
  endif()
else()
  message(
    WARNING
      "your compiler is not yet able to compile all examples under the C++17 standard, some compilations may fail"
    )
endif()

add_executable(attributes src/attributes.cpp)

add_executable(default_member_initializtion src/default_member_initializtion.cpp)

add_executable(init_statements src/init_statements.cpp)

add_executable(keyword_constexpr src/keyword_constexpr.cpp)

add_executable(keyword_default_delete src/keyword_default_delete.cpp)

add_executable(std_algorithms src/std_algorithms.cpp)

add_executable(std_move src/std_move.cpp)

add_executable(std_string_view src/std_string_view.cpp)

add_executable(std_tuple_std_get src/std_tuple_std_get.cpp)

add_executable(std_chrono src/std_chrono.cpp)

if(DEFINED ENABLE_CPP20_FEATURES)
  message(INFO "Building C++20 features (Not supported by all compilers)")

  add_executable(cpp20_keyword_constinit_consteval src/cpp20_keyword_constinit_consteval.cpp)
  target_compile_options(cpp20_keyword_constinit_consteval
                         PRIVATE --std=c++2a)

  add_executable(cpp20_ranges src/cpp20_ranges.cpp)
  target_compile_options(cpp20_ranges
                         PRIVATE --std=c++2a)

  add_executable(cpp20_threeway_comparison src/cpp20_threeway_comparison.cpp)
  target_compile_options(cpp20_threeway_comparison
                         PRIVATE --std=c++2a)

endif()