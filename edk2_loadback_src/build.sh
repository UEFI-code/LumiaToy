export MODULE_PATH=$(pwd)
export GCC5_ARM_PREFIX=arm-linux-gnueabi-

rm -rf MyApp
cp MdeModulePkg.dsc ~/edk2_arm32/MdeModulePkg/MdeModulePkg.dsc

cd ~/edk2_arm32
source edksetup.sh
build \
    -a ARM \
    -p MdeModulePkg/MdeModulePkg.dsc \
    -m $MODULE_PATH/MyApp.inf \
    -t GCC5