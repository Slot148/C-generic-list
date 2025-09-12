cmake_minimum_required(VERSION 3.10)
project(lista)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(Tlist src/lib/Tlist/Tlist.c)
target_compile_options(Tlist PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(Tlist PUBLIC headers)

add_executable(meu_programa src/main.c)
target_link_libraries(meu_programa PRIVATE Tlist)