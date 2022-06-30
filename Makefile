flash:
	openocd -f openocd.cfg -c "verify"

monitor:
	python3 -m serial.tools.miniterm --raw /dev/ttyACM0 921600
