# Pulseaudio setup

1. sudo apt-get update
1. sudo apt-get install pulseaudio meson bc autopoint libfftw3-dev gettext libgettextpo-dev libxml2-utils liblist-moreutils-perl autoconf libtool libxml-parser-perl libglib2.0-dev libssl1.1
1. `daemon.conf` - положить в <path_to_mount_point>/etc/pulse/`
1. `default.pa` - положить в `<path_to_mount_point>/etc/pulse/`
1. включить pulseaudio, для этого запустить `raspi-config`, выбрать `6 Advanced Options` -> `A7 Audio Config` -> `1 Pulse Audio`

Все пакеты, указанные ниже, собираются на устройстве

# LADSPA build and install
1. cd ~/
1. git clone https://github.com/swh/ladspa.git ladspa
1. cd ladspa
1. autoreconf -i
1. ./configure
1. make
1. sudo make install

# Equalizer build and setup
1. cd ~/
1. git clone https://github.com/pulseaudio-equalizer-ladspa/equalizer.git equalizer
1. cd equalizer
1. meson build
1. cd build
1. ninja
1. sudo ninja install
1. на устройстве запустить pulseaudio-equalizer enable-config

В качестве playback/record устройства использовать `pulse (default)`

Запуск GUI эквалайзера: DISPLAY=:0 pulseaudio-equalizer-gtk




