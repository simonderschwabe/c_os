#!/bin/bash

scripts/bin/grub --batch --device-map=/dev/null << EOF
device (fd0) floppy.img
root (fd0)
setup (fd0)
quit
EOF
