test:
	/home/dusted/data/Misc/bin/arduino-1.8.6/arduino --verify main.ino

connect:
	minicom -D /dev/ttyACM0 -b 9600	
