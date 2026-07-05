rm -rf MyApp
cp ArmVirtQemu.dsc ~/edk2_arm32/ArmVirtPkg/

cd ~/edk2_arm32
source edksetup.sh
export GCC5_ARM_PREFIX=arm-linux-gnueabi-
build -a ARM -t GCC5 -p ArmVirtPkg/ArmVirtQemu.dsc