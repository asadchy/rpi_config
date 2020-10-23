#!/bin/sh

PATH_TO_GPIO_CLASS="/sys/class/gpio"
PATH_TO_GPIO_FOLDER="/dev/gpio"

# $1 - gpio num, $2 - direction (in/out), $3 - name
config_pin_and_create_link() {
	echo $1 > $PATH_TO_GPIO_CLASS/export
	echo $2 > $PATH_TO_GPIO_CLASS/gpio$1/direction
	ln -s $PATH_TO_GPIO_CLASS/gpio$1/value $PATH_TO_GPIO_FOLDER/$3
}

mkdir $PATH_TO_GPIO_FOLDER

#configure OC1...OC4 pins as inputs
config_pin_and_create_link "496" "in" "OC1"
config_pin_and_create_link "497" "in" "OC2"
config_pin_and_create_link "498" "in" "OC3"
config_pin_and_create_link "499" "in" "OC4"

#configure GPB6, GPB7, GPA7 as inputs
config_pin_and_create_link "502" "in" "GPB6"
config_pin_and_create_link "503" "in" "GPB7"
config_pin_and_create_link "495" "in" "GPA7"

#configure GPIO25, GPIO26 as inputs
config_pin_and_create_link "25" "in" "GPIO25"
config_pin_and_create_link "26" "in" "GPIO26"

#configure GPIO16, GPIO27, GPIO45 as outputs
config_pin_and_create_link "16" "out" "GPIO16"
config_pin_and_create_link "27" "out" "GPIO27"
config_pin_and_create_link "45" "out" "GPIO45"

#configure tx_enable (GPIO17) as output
config_pin_and_create_link "17" "out" "TX_ENABLE"

#configure RL1, RL2 as outputs
config_pin_and_create_link "488" "out" "RL1"
config_pin_and_create_link "489" "out" "RL2"

#configure IRLED_ON as output
config_pin_and_create_link "490" "out" "IRLED_ON"

#configure IRFILTER_ON as output
config_pin_and_create_link "22" "out" "IRFILTER_ON"

#configure HEAT_ON as output
config_pin_and_create_link "35" "out" "HEAT_ON"
