import os
# l = []
# for a in open('PRIMESASTEXT').readlines():
# 	# if int()
# 	print int(a)


for a in open('words27.txt').readlines():
	print a, ' ', os.popen("./factorize "+a).readline()