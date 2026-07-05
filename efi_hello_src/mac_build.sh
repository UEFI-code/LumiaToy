/opt/homebrew/opt/llvm/bin/clang \
  -target armv7-none-eabi \
  -ffreestanding \
  -fno-pic \
  -marm \
  -c 1.c \
  -o 1.o

/opt/homebrew/opt/lld/bin/ld.lld \
    -m armelf \
    -T linker.ld \
    -e efi_main \
    1.o \
    -o 1.elf