#!/usr/bin/env bash

MCU=atmega328p
PORT=$(pavr2cmd --prog-port)
TARGET=bootloader_atmega32u4_1.0.0.hex

avrdude -c stk500v2 -P "${PORT}" -p $MCU -U flash:w:$TARGET:i