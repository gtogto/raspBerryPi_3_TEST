import serial

serport = serial.Serial("/dev/ttyS2", 115200, timeout=1)
while True:
    while serport.inWaiting() > 0:
		c = serport.read()
		print c
