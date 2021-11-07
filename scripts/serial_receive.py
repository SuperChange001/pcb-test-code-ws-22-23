import serial
import matplotlib.pyplot as plt

ser = serial.Serial("/dev/ttyACM0", 500000)

plt.ion()

while True:
	ser.write(b't')
	data_rd_byte_array = (ser.readline())
	data_as_string_list = data_rd_byte_array.decode("utf-8").split(',')[:-1]

	data_as_int_list = [int(i) for i in data_as_string_list]
	# print((len(data_as_int_list)))
	plt.plot(range(len(data_as_int_list)),data_as_int_list)
	plt.pause(0.0001) # not necessary atm
	plt.clf()
	plt.ylim(0, 5000)

