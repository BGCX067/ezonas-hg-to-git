import struct

f = open("BIGFILES/NUMBERS.BIT")
l = []

d = {}
for a in sorted(open('BIGFILES/alphabet27.txt').readlines()):
	l = a.split(' ')
	d[int(l[2])] = l[1].upper()

while(True):
	cont = f.read(8)
	if(cont == ''): break
	n = struct.unpack('Q',cont)[0]
	if(n in d):
		print d[n]
	# l.append(struct.unpack('Q',cont)[0])

# 
# f = open("NUMBERS.BIT")
# while(True):
# 	cont = f.read(8)
# 	if(cont == ''): break
# 	print struct.unpack('Q',cont)[0]


# for k in sorted(d.iterkeys()):
# 	# print k, d[k]
# 	print k, d[k], 
# 
