rtl8723du
===========
This repository includes drivers for the following card:

Realtek RTL8723DU

### Installation instruction
##### Requirements
You will need to install "make", "gcc", "kernel headers", "kernel build essentials", and "git".

For **Ubuntu**: You can install them with the following command
```bash
sudo apt-get update
sudo apt-get install make gcc linux-headers-$(uname -r) build-essential git
```
For **Fedora**: You can install them with the following command
```bash
sudo dnf install kernel-headers kernel-devel
sudo dnf group install "C Development Tools and Libraries"
```
For **openSUSE**: Install necessary headers with
```bash
sudo zypper install make gcc kernel-devel kernel-default-devel git libopenssl-devel
```
For **Arch**: After installing the necessary kernel headers and base-devel,
```bash
git clone https://aur.archlinux.org/rtw89-dkms-git.git
cd rtw89-dkms-git
makepkg -sri
```
If any of the packages above are not found check if your distro installs them like that.

##### Installation
For all distros:
```bash
git clone git://github.com/lwfinger/rtl8723du.git -b v5.13.4
cd rtl8723du
make
sudo make install
```

##### How to unload/reload a Kernel module
 ```bash
sudo modprobe -rv 8723du         #This unloads the module
sudo modprobe -v 8723du          #This loads the module
```

***********************************************************************************************

When your kernel changes, then you need to do the following:
```bash
cd ~/rtl8723du
git pull
make clean
make
sudo make install
```

Remember, this MUST be done whenever you get a new kernel - no exceptions.

