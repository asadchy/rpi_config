#!/bin/sh

echo 491 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio491/direction
echo 1 > /sys/class/gpio/gpio491/value
sleep 10
pppd call a-gsm
