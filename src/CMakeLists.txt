set(SOURCES
  "colors.cpp"
  "colors.h"
  "console.cpp"
  "console.h"
  "emoji.cpp"
  "emoji.h"
  "emoji-data.cpp"
  "emoji-data.h"
  "markdown.cpp"
  "markdown.h"
  "platform.h"
  "platform.cpp"
  "platform-factory.h"
  "platform-factory.cpp"
  "platform-posix.h"
  "platform-posix.cpp"
  "platform-windows.h"
  "platform-windows.cpp"
)

set(LIB_NAME ${PROJECT_NAME}_lib)

add_library(${LIB_NAME} STATIC ${SOURCES})

set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (NOT USE_AS_LIBRARY)
  add_executable(${PROJECT_NAME} main.cpp)

  find_package(Sanitizers)
  add_sanitizers(${LIB_NAME})
  add_sanitizers(${PROJECT_NAME})

  target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
endif()

if (MSVC)
  target_compile_options(${LIB_NAME} PRIVATE "/IW4")
  target_compile_options(${LIB_NAME} PRIVATE "/WX")
else()
  target_compile_options(${LIB_NAME} PRIVATE "-Wall")
  target_compile_options(${LIB_NAME} PRIVATE "-Wextra")
  target_compile_options(${LIB_NAME} PRIVATE "-Werror")
  target_compile_options(${LIB_NAME} PRIVATE "-pedantic")
endif()
