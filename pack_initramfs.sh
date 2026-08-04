cd initramfs_root
find . | cpio -o -H newc | gzip > ../new_initramfs.cpio.gz