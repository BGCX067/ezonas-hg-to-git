
def show_base(base, interval = [64, 256]):
	print "base", base
	max = 100
	exp2 = interval[1]
	while exp2 >= interval[0]:
		while base ** max > 2 ** exp2:
			max -= 1
		print base, "^", max, "< 2 ^",  exp2
		exp2 -= 64

show_base(26)
show_base(27)
