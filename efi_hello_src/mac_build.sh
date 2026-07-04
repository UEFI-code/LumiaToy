/opt/homebrew/opt/llvm/bin/clang \
  -target armv7-none-windows \
  -ffreestanding \
  -c 1.c \
  -o 1.o

/opt/homebrew/opt/lld/bin/ld.lld \
  -shared \
  -m thumb2pe \
  --subsystem=efi_application \
  -e efi_main \
  1.o \
  -o 1.efi