export MODULE_PATH=$(pwd)
export GCC5_ARM_PREFIX=arm-none-eabi-

rm -rf MyApp
cp MdeModulePkg_mac.dsc ~/edk2_arm32/MdeModulePkg/MdeModulePkg.dsc

cd ~/edk2_arm32
source edksetup.sh
build \
    -a ARM \
    -p MdeModulePkg/MdeModulePkg.dsc \
    -m $MODULE_PATH/MyApp.inf \
    -t GCC5