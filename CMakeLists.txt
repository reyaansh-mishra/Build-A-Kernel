cmake_minimum_required(VERSION 3.20)
project(BuildAKernel LANGUAGES C CXX ASM)

set(TARGET_TRIPLE i686-elf)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)

set(CMAKE_C_COMPILER_TARGET ${TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${TARGET_TRIPLE})
set(CMAKE_ASM_COMPILER_TARGET ${TARGET_TRIPLE})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE ASM arch/*.s)
file(GLOB_RECURSE ARCH arch/*.cpp)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(kernel.bin
    ${ASM}
    ${ARCH}
    ${SRC}
)

target_compile_options(kernel.bin PRIVATE
    -ffreestanding
    -fno-builtin
    -fno-exceptions
    -fno-rtti
    -fno-threadsafe-statics
    -fno-stack-protector
    -Wall
    -Wextra
    -O2
    -fno-stack-protector
    -fno-pic
    -fno-pie
    -fno-asynchronous-unwind-tables
)

target_link_options(kernel.bin PRIVATE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/arch/x86/linker.ld
    -nostdlib
    -fuse-ld=lld
    -no-pie
)