cmake_minimum_required(VERSION 3.20)

project(flibc LANGUAGES C ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
    -fno-stack-protector
    -fno-sanitize=undefined
    -Wall
    -Wextra
    -Wno-unused-parameter
)

set(FLIBC_SOURCES
    io/write.c
    misc/errno.c
    misc/stack_chk.c
    stdlib/exit/exit.c
    stdlib/exit/_exit.c
    stdio-common/printf/printf.c
    stdio-common/printf/snprintf.c
    stdio-common/printf/engine/printf_engine.c
    stdio-common/output/puts.c
    stdio-common/output/fputs.c
    string/mem/memcpy.c
    string/mem/memmove.c
    string/mem/memset.c
    string/mem/memcmp.c
    string/str/strlen.c
    string/str/strcmp.c
    string/str/strncmp.c
    string/str/strcpy.c
    string/str/strncpy.c
    string/str/strchr.c
    string/str/strrchr.c
    arch/aarch64/crt/_start.S
)

add_library(flibc STATIC ${FLIBC_SOURCES})

target_include_directories(flibc PUBLIC include)

target_compile_options(flibc PRIVATE -nostdlib -ffreestanding)
