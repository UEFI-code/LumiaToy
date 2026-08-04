mkdir initramfs_root
cd initramfs_root
gzip -dc ../initramfs.cpio.gz | cpio -idmv