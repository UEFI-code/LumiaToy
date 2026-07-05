cd ~
sudo apt install -y build-essential git python3-distutils python3-pip uuid-dev iasl gcc-aarch64-linux-gnu gcc-arm-linux-gnueabi
git clone -b edk2-stable202302 https://github.com/tianocore/edk2.git edk2_arm32
cd edk2_arm32
git submodule update --init --recursive
make -C BaseTools