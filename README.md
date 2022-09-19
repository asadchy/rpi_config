# Собираем систему

1. `kernel_build.txt` - инструкция по сборке системы

# Конфиги для RPI

1. `.config` - конфиг ядра для сборки.\
Положить в корневую папку ядра.
1. `config.txt` - конфиг RPI.\
Положить в `/boot`.
1. `dt-blob.bin` - конфиг GPU (для конфигурации камеры).\
Положить в `/boot`.
1. `dt-blob-cam1.dts` - вышеупомянутый конфиг в формате dts.\
Нужен на случай необходимости внести изменения.
1. `asound.conf` - конфиг аудио кодека.\
Положить в `/rootfs/etc`.
1. `asound.state` - конфиг аудио кодека.\
Положить в `/rootfs/var/lib/alsa/asound.state`.
1. `mkdir /rootfs/etc/gpio`
1. `gpio.sh` - положить в `/rootfs/etc/gpio`
1. `rc.local` - положить в `/etc/rc.local` (заменить существующий файл).

# Настройка GSM модема

1. Непосредственно на малине: `sudo apt-get install network-manager`

1. `NetworkManager.conf` положить в `/etc/NetworkManager`
1. `ETH.nmconnection` и `GSM.nmconnection` положить в `/etc/NetworkManager/system-connections`
1. `dhcpcd.conf` положить в `/etc/'
1. `mkdir /rootfs/etc/gsm`
1. `gsm_modem.sh` - положить в `/rootfs/etc/gsm`
1. `sudo chown root:root gsm_modem.sh` (устанавливаем root в качестве владельца).\
