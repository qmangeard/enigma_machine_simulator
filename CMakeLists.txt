cmake_minimum_required(VERSION 3.16)

project(enigma_machine_simulator VERSION 0.1.0 LANGUAGES C)

add_executable(prog
    apps/cli/main.c
    apps/cli/cli_input.c
    src/enigma/input.c
)

target_include_directories(prog PRIVATE
    include
)

target_compile_features(prog PRIVATE c_std_11)

target_compile_options(prog PRIVATE
    -Wall
    -Wextra
    -Werror
)