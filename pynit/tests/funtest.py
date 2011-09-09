def fun(l, m, n = 2):
	print "oh"
def fon(o, p):
	print "ah"
	
	f = fun
for i in range(10):
	if i % 2:
		f = fon
	else:
		f = fun
	f(1, 2)
		