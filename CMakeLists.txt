cmake_minimum_required (VERSION 3.6)
project (ParseFloat)

include(CheckLibraryExists)

# check if we need to link against libm
check_library_exists(m pow "" LIBM)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    set(CMAKE_C_FLAGS_RELEASE "/O3")
    set(CMAKE_C_FLAGS_DEBUG "/g")
    set(CMAKE_C_FLAGS "/W2")
else()
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Wmissing-prototypes -Wshadow -Wpointer-arith -Wcast-qual -Wwrite-strings -Wno-unused-parameter -fstrict-aliasing")
endif()

# libhodlr
add_library(strtodouble STATIC strtodouble.c)
if(${LIBM})
    target_link_libraries(strtodouble m)
endif()

# caps frontend exectuable
add_executable(tests tests.c)
if(${LIBM})
    target_link_libraries(tests m)
endif()
target_link_libraries(tests strtodouble)
