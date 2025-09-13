cmake_minimum_required(VERSION 3.10)
project(lista)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(Tlist lib/Tlist.c test/test.c)
target_compile_options(Tlist PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(Tlist PUBLIC include)

add_executable(meu_programa test/main.c)
target_link_libraries(meu_programa PRIVATE Tlist)