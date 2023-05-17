This repository has an empty program for esp32 that should compile
on adJ/OpenBSD 7.2 with makeEspArduino but fails.


On OpenBSD/adJ 7.2 install:

	doas pkg_add makeesparduino \
		arduino \
		arduino-esp32 \
		arduino-makefile \
		py3-esptool \
		xtensa-esp32-elf-gcc \
		xtensa-esp32-elf-binutils \
		xtensa-esp32-elf-newlib \
		mkspiffs \
		gmake


Then clone this repository and run from its directory:

	gmake

It will start compilation but it will fail in esp32-hal-gpio.c with a lot
of errors like:

```
/usr/local/xtensa-esp32-elf/xtensa-esp32-elf/include/wchar.h:75:16:
error: conflicting declaration 'typedef __FILE FILE'
 typedef __FILE FILE;
                ^~~~
In file included from
/usr/local/share/arduino/hardware/espressif/esp32/cores/esp32/HardwareSerial.cpp:2:
/usr/local/avr/include/stdio.h:277:23: note: previous declaration as 'typedef
struct __file FILE'
 typedef struct __file FILE;

```

If in the source file you change:

	#if defined(__AVR__)
	#include <SoftwareSerial.h>
	#endif

with
	#if defined(__AVR__)
	//#include <SoftwareSerial.h>
	#endif

The problem will no happen.


The generated files are trying to use at the same time libc for esp32 and
libc for avr. 
The problem is that makeEspArduino tries to add SerialSoftware
alghough it is referenced inside a section `#if defined(__AVR__)` 
--the symbol `__AVR__` is not defined when using esp32, so the
`#include <SoftwareSerial.h>` should be ignored but it seems
the algorithm used by makeEspArduino to decide what to compile 
ignores the directive `#if`.
