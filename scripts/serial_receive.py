import serial
ser = serial.Serial("/dev/ttyACM0", 115200)
while True:
     cc=str(ser.readline())
     print(cc)