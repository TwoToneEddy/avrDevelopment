A repo containing notes and working examples of AVR development.

I'm using an arduino uno as the ISP programmer via the ICSP header. I'm using avrdude on linux. Here is an example using avrdude to upload a hex via the uno:

avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM2 -b19200 -Uflash:w:blink.hex

Note, the lack of the -D option means i've over writing the bootloader which is fine, I don't want one.

Good Video: https://www.youtube.com/watch?v=9WeewNNGs5E

Getting started:

	Chip may or may not come with the correct fuse settings. If it comes configured for an external clock you won't be able to do anything with the chip on its own.

	1. Plug chip into empty Arduino UNO.
	2. Connect the arduino ISP to this UNO target:

		ISP		Target

		10		reset
		11		11
		12		12
		13		13
		5V		5V
		0V		0V	

	3. Set fuses to use internal clock:

		avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM1 -b19200 -Ulfuse:w:0xF2:m
		avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM1 -b19200 -Uhfuse:w:0xDE:m
		avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM1 -b19200 -Uefuse:w:0xFD:m	


Useful commands:
	Read fuses:
	avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM1 -b19200 -Ulfuse:r:

	Write fuses:
	avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM1 -b19200 -Ulfuse:w:0x72:m


Fuse settings:

	dip chip
	8mhz internal
	board_fuses.lfuse = 0xF2
	board_fuses.hfuse = 0xDE
	board_fuses.efuse = 0xFD

	1mhz internal
	board_fuses.lfuse = 0x72
	board_fuses.hfuse = 0xDE
	board_fuses.efuse = 0xFD

	smt
	from factory:
	board_fuses.lfuse = 0x62
	board_fuses.hfuse = 0xD9
	board_fuses.efuse = 0xFF
