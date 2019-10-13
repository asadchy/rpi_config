# Конфиги для RPI

1. .config - конфиг ядра для сборки (положить в корневую папку ядра)
2. config.txt - конфиг файл RPI (положить в раздел /boot)
3. dt-blob.bin - конфиг GPU (для конфигурации камеры) (положить в /boot)
4. dt-blob-cam1.dts - вышеупомянутый конфиг в формате dts (на случай необходимости внести изменения)
5. asound.conf - конфиг аудио кодека (положить в /rootfs/etc)
6. asound.state - конфиг аудио кодека (положить в /rootfs/var/lib/alsa/asound.state)

# Настройка GSM модема

1. mkdir /rootfs/etc/ppp/chat
2. a-gsm_chat - положить в /rootfs/etc/ppp/chat/a-gsm (a-gsm_chat должен быть переименован в a-gsm)
3. mkdir /rootfs/etc/ppp/peers
4. a-gsm_peers - положить в /rootfs/etc/ppp/peers/a-gsm (a-gsm_peers должен быть переименован в a-gsm)
5. /rootfs/etc/ppp/chat/a-gsm - в данном файле по умолчанию установлен APN для оператора A1, в случае использования другого оператора, данные APN должен быть изменен
6. rc.local - положить в /etc/rc.local (заменить существующий файл)
7. mkdir /rootfs/etc/gsm
8. gsm_modem.sh - положить в /rootfs/etc/gsm и установить root в качестве владельца и группы (sudo chown root:root gsm_modem.sh)
9. непосредственно на малине установить демона pppd (sudo apt-get install pppoe)




