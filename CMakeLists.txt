cmake_minimum_required(VERSION 3.9)

project(fun-console CXX)

set(USE_AS_LIBRARY ON)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(USE_AS_LIBRARY OFF)
endif ()

if (NOT USE_AS_LIBRARY)
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

if (NOT USE_AS_LIBRARY)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
  add_subdirectory(thirdparty/benchmark)

  add_subdirectory(thirdparty/catch)
  add_subdirectory(test)
  if ((NOT SANITIZE_ADDRESS) AND (NOT SANITIZE_THREAD) AND (NOT SANITIZE_UNDEFINED))
      add_subdirectory(bench)
  endif ()
endif()
