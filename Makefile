flash:
	openocd -f interface/stlink.cfg -f target/stm32l0.cfg -c "program build/src/apps/LoRaMac/LoRaMac-periodic-uplink-lpp verify reset exit"