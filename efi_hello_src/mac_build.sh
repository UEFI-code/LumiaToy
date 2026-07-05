/opt/homebrew/opt/llvm/bin/clang \
  -target armv7-none-eabi \
  -ffreestanding \
  -fno-pic \
  -marm \
  -c 1.c \
  -o 1.o

/opt/homebrew/opt/lld/bin/lld-link \
  /subsystem:efi_application \
  /entry:efi_main \
  /machine:arm \
  /base:0x10000000 \
  /align:4096 \
  1.o /out:1.efi