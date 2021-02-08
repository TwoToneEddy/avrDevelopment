A repo containing notes and working examples of AVR development.

I'm using an arduino uno as the ISP programmer via the ICSP header. I'm using avrdude on linux. Here is an example using avrdude to upload a hex via the uno:

avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cstk500v1 -P/dev/ttyACM2 -b19200 -Uflash:w:blink.hex

Note, the lack of the -D option means i've over writing the bootloader which is fine, I don't want one.
