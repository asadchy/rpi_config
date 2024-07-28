# Кросс-компилятор:

1. `sudo apt install bc bison flex libssl-dev make libc6-dev libncurses5-dev`
1. `sudo apt install crossbuild-essential-armhf`

# Ядро:

1. `git clone https://github.com/asadchy/linux.git`
1. Зайти в склонированную директорию и переключить ветку `git checkout rpi-6.6.y`
1. `git clone https://github.com/asadchy/rpi_config.git`
1. Зайти в склонированную директорию и переключить ветку `git checkout rpi-6.6.y`
1. Файл `.config` из директории `rpi_config` скопировать в директорию `linux`.
1. Перейти в директорию `linux`.
1. `make -j8 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs` (компилируем ядро, модули, dtb)
1. После окончания компиляции, подключить SD-карту.
1. Все последующие команды выполняются из директории `linux`.
1. `sudo cp arch/arm/boot/zImage <path_to_mount_point>/boot/firmware/kernel7.img`
1. `sudo cp arch/arm/boot/dts/overlays/*.dtb* <path_to_mount_point>/boot/firmware/overlays/`
1. `sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=<path_to_mount_point>/ modules_install`

# Последующая конфигурация:

1. Проделать все операции из описания в `rpi_config/README.md`.
