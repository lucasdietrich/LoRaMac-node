flash:
	openocd -f interface/stlink.cfg -f target/stm32l0.cfg -c "program build/src/apps/playground/playground-periodic-uplink-lpp verify reset exit"

monitor:
	python3 -m serial.tools.miniterm /dev/ttyACM0 921600
	# screen /dev/ttyACM1 921600
