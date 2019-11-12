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

# Настройка GSM модема

1. `mkdir /rootfs/etc/ppp/chat`
1. `a-gsm_chat` - положить в `/rootfs/etc/ppp/chat/a-gsm`.\
`a-gsm_chat` должен быть переименован в `a-gsm`.
1. `mkdir /rootfs/etc/ppp/peers`
1. `a-gsm_peers` - положить в `/rootfs/etc/ppp/peers/a-gsm`.\
`a-gsm_peers` должен быть переименован в `a-gsm`.
1. `/rootfs/etc/ppp/chat/a-gsm` - в данном файле по умолчанию установлен APN для оператора A1.\
В случае использования другого оператора, APN должен быть изменен
1. `rc.local` - положить в `/etc/rc.local` (заменить существующий файл).
1. `mkdir /rootfs/etc/gsm`
1. `gsm_modem.sh` - положить в `/rootfs/etc/gsm`
1. `sudo chown root:root gsm_modem.sh` (устанавливаем root в качестве владельца).\
1. Непосредственно на малине: `sudo apt-get install pppoe` (устанавливаем демона pppd).
