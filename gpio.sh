#!/bin/sh -e

PATH_TO_GPIO_CLASS="/sys/class/gpio"
PATH_TO_GPIO_FOLDER="/dev/gpio"

# $1 - gpio num, $2 - direction (in/out), $3 - name
config_pin_and_create_link() {
	echo $1 > $PATH_TO_GPIO_CLASS/export
	echo $2 > $PATH_TO_GPIO_CLASS/gpio$1/direction
	ln -f -s $PATH_TO_GPIO_CLASS/gpio$1/value $PATH_TO_GPIO_FOLDER/$3
}

mkdir $PATH_TO_GPIO_FOLDER

#configure OC1...OC4 pins as inputs
config_pin_and_create_link "582" "in" "OC1"
config_pin_and_create_link "583" "in" "OC2"
config_pin_and_create_link "584" "in" "OC3"
config_pin_and_create_link "585" "in" "OC4"

#configure GPB6, GPB7, GPA7 as inputs
config_pin_and_create_link "588" "out" "IRFILTER_ON"
config_pin_and_create_link "589" "in" "GPB7"
config_pin_and_create_link "581" "in" "GPA7"

#configure GPIO26 as inputs
config_pin_and_create_link "538" "in" "GPIO26"

#configure GPIO16, GPIO27, GPIO45 as outputs
config_pin_and_create_link "528" "out" "GPIO16"

#configure tx_enable (GPIO17) as output
config_pin_and_create_link "529" "out" "TX_ENABLE"

#configure RL1, RL2 as outputs
config_pin_and_create_link "574" "out" "RL1"
config_pin_and_create_link "575" "out" "RL2"

#configure IRLED_ON as output
config_pin_and_create_link "576" "out" "IRLED_ON"

#configure HEAT_ON as output
config_pin_and_create_link "547" "out" "HEAT_ON1"
config_pin_and_create_link "520" "out" "HEAT_ON2"

exit 0
