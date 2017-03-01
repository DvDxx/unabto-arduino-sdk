# Build status
[![Build Status](https://travis-ci.org/nabto/unabto-arduino-sdk.svg?branch=master)](https://travis-ci.org/nabto/unabto-arduino-sdk)

# Arduino example



This demo shows how to use the nabto request response model on the
atmel AVR platform. The demos has been made such that they can be executed on the Arduino MEGA boards with the Wiznet W5100 ethernet shield. (Ethernet module version 1).

## How to compile

```
mkdir build
cd build
cmake -DBOARD=MEGA -DCMAKE_TOOLCHAIN_FILE=`pwd`/../demo/toolchain.cmake ../demo
make
```

There is a compiler bug in avr-gcc 4.9+ so we recommend using a
version without bugs.

## How to run on the Arduino MEGA

After the code is compiled for the MEGA board it can be uploaded to
the mega board with avrdude.

```
avrdude -v -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:main.hex
```

## Test Level

This is a demo project and use the code as such.
