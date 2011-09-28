import struct

f = open("NUMBERS.BIT")
l = []
while(True):
	cont = f.read(8)
	if(cont == ''): break
	# print struct.unpack('Q',cont)[0]
	l.append(struct.unpack('Q',cont)[0])