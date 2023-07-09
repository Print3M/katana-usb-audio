#!/usr/bin/env bash

MODULE="katana_usb_audio"

set -ueo pipefail

rmmod "$MODULE"
rmmod "snd-usb-audio"
make clean
make
insmod "${MODULE}.ko"
echo -e "\nModule $MODULE recompiled and reloaded."