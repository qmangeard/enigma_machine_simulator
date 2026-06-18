cmake_minimum_required(VERSION 3.16)

project(enigma_machine_simulator VERSION 0.1.0 LANGUAGES C)

add_executable(enigma_cli
    apps/cli/main.c
    apps/cli/cli_input.c
    src/enigma/input.c
)

target_include_directories(enigma_cli PRIVATE
    include
)

target_compile_features(enigma_cli PRIVATE c_std_11)

target_compile_options(enigma_cli PRIVATE
    -Wall
    -Wextra
    -Werror
)