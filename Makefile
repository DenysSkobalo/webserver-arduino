BOARD = esp8266:esp8266:nodemcuv2
PORT  = /dev/cu.usbserial-1130

PROJECT ?= webserver-arduino
SKETCH  = $(PROJECT)/$(PROJECT).ino

all: compile

compile:
	arduino-cli compile --fqbn $(BOARD) $(SKETCH)

upload: compile
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) $(SKETCH)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=115200

clean:
	rm -rf build

