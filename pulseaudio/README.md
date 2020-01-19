# Pulseaudio setup

1. sudo apt-get update
1. sudo apt-get install pulseaudio pulseaudio-equalizer pulseaudio-utils
1. `daemon.conf` - положить в `/rootfs/etc/pulse/`
1. `default.pa` - положить в `/rootfs/etc/pulse/`

В качестве playback/record устройства использовать `pulse (default)`

Запуск GUI эквалайзера: DISPLAY=:0 qpaeq
