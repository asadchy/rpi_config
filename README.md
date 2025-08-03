# Собираем систему

1. `kernel_build.txt` - инструкция по сборке системы

# Конфиги для RPI

1. `config.txt` - конфиг RPI.\
Положить в `<path_to_mount_point>/boot/firmware`.
1. `dt-blob.bin` - конфиг GPU (для конфигурации камер).\
Положить в `/boot/firmware`.
1. `dt-blob.dts` - вышеупомянутый конфиг в формате dts.\
Нужен на случай необходимости внести изменения.
1. `asound.conf` - конфиг аудио кодека.\
Положить в `<path_to_mount_point>/etc`.
1. `asound.state` - конфиг аудио кодека.\
Положить в `<path_to_mount_point>/var/lib/alsa/asound.state`.
1. `mkdir <path_to_mount_point>/etc/gpio`
1. `gpio.sh` - положить в `<path_to_mount_point>/etc/gpio`
1. `rc.local` - положить в `<path_to_mount_point>/etc/rc.local` (заменить существующий файл).

# Настройка GSM модема

1. Непосредственно на малине: `sudo apt-get install network-manager`

1. `NetworkManager.conf` положить в `<path_to_mount_point>/etc/NetworkManager`
1. `ETH.nmconnection` и `GSM.nmconnection` положить в `<path_to_mount_point>/etc/NetworkManager/system-connections`
1. `dhcpcd.conf` положить в `<path_to_mount_point>/etc/'
1. `mkdir <path_to_mount_point>/etc/gsm`
1. `gsm_modem.sh` - положить в `<path_to_mount_point>/etc/gsm`
1. `sudo chown root:root gsm_modem.sh` (устанавливаем root в качестве владельца).\

