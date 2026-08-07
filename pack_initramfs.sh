cd initramfs_root
find . | cpio -o -H newc | gzip > ../initramfs.cpio.gz