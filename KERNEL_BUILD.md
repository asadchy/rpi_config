# Кросс-компилятор:

1. `apt-get install git rsync cmake ia32-libs`
1. `git clone https://github.com/asadchy/tools.git`
1. `export PATH=$PATH:<path_to_cloned_repo>/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin`

Если всё было сделано правильно, то при выполнении
`arm-linux-gnueabihf-gcc -v`
должен быть следующий вывод:

```
Target: arm-linux-gnueabihf
Configured with: /cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/src/gcc-linaro-4.8-2014.01/configure --build=i686-build_pc-linux-gnu --host=i686-build_pc-linux-gnu --target=arm-linux-gnueabihf --prefix=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/install --with-sysroot=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/install/arm-linux-gnueabihf/libc --enable-languages=c,c++,fortran --disable-multilib --enable-multiarch --with-arch=armv6 --with-tune=arm1176jz-s --with-fpu=vfp --with-float=hard --with-pkgversion='crosstool-NG linaro-1.13.1-4.8-2014.01 - Linaro GCC 2013.11' --with-bugurl=https://bugs.launchpad.net/gcc-linaro --enable-__cxa_atexit --enable-libmudflap --enable-libgomp --enable-libssp --with-gmp=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --with-mpfr=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --with-mpc=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --with-isl=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --with-cloog=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --with-libelf=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/.build/arm-linux-gnueabihf/build/static --enable-threads=posix --disable-libstdcxx-pch --enable-linker-build-id --enable-plugin --enable-gold --with-local-prefix=/cbuild/slaves/oorts/crosstool-ng/builds/arm-linux-gnueabihf-raspbian-linux/install/arm-linux-gnueabihf/libc --enable-c99 --enable-long-long --with-float=hard
Thread model: posix
gcc version 4.8.3 20140106 (prerelease) (crosstool-NG linaro-1.13.1-4.8-2014.01 - Linaro GCC 2013.11)
```

# Ядро:

1. `git clone https://github.com/asadchy/linux.git`
1. `git clone https://github.com/asadchy/rpi_config.git`
1. Файл `.config` из директории `rpi_config` скопировать в директорию `linux`.
1. Перейти в директорию `linux`.
1. `make -j8 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs` (компилируем ядро, модули, dtb)
1. После окончания компиляции, подключить SD-карту.
1. Все последующие команды выполняются из директории `linux`.
1. `sudo cp arch/arm/boot/zImage <path_to_mount_point>/boot/kernel7.img`
1. `sudo cp arch/arm/boot/dts/*.dtb <path_to_mount_point>/boot/`
1. `sudo cp arch/arm/boot/dts/overlays/*.dtb* <path_to_mount_point>/boot/overlays/`
1. `sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=<path_to_mount_point>/rootfs/ modules_install`

# Последующая конфигурация:

1. Проделать все операции из описания в `rpi_config/README.md`.
