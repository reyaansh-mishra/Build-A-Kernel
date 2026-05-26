cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)
project(BUILD-A-KERNEL CXX ASM)

set(CMAKE_LINKER ld.lld)
set(CMAKE_CXX_LINK_EXECUTABLE "ld.lld <LINK_FLAGS> <OBJECTS> -o <TARGET>")

set(CMAKE_LINK_DEPENDS_NO_SHARED 1)
set(CMAKE_DEPFILE_FLAGS_LINKER "")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-i386.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE KERNEL_SOURCES
    "src/*.cpp"
    "src/*.s"
    "Includes/*.hpp"
)

add_executable(kernel ${KERNEL_SOURCES})

target_compile_options(kernel PRIVATE
    -std=c++20
    --target=i386-none-elf
    -march=i386
    -ffreestanding
    -nostdlib
    -fno-stack-protector
    -m32
    -fno-exceptions
    -fno-rtti
    -fno-pic
    -fno-threadsafe-statics
    -g
)
target_include_directories(kernel PRIVATE
    ${CMAKE_SOURCE_DIR}/Includes
)

target_link_options(kernel PRIVATE -m elf_i386 -T ${CMAKE_SOURCE_DIR}/src/boot/arch/x86/linker.ld)


add_custom_target(run
    COMMAND cp ${CMAKE_BINARY_DIR}/kernel iso/boot/kernel
    COMMAND grub-mkrescue -o kernel.iso iso
    COMMAND qemu-system-i386 -d cpu_reset -no-reboot -no-shutdown -cdrom kernel.iso -s
    DEPENDS kernel
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)