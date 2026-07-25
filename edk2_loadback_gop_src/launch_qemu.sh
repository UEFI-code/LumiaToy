qemu-system-arm \
    -machine virt \
    -m 512M \
    -bios /opt/homebrew/share/qemu/edk2-arm-code.fd \
    -device virtio-gpu-pci \
    -display default \
    -serial stdio \
    -drive format=raw,file=fat:rw:.