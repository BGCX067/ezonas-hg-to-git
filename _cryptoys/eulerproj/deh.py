def calc_squared_sum(top):
	r = 0
	for i in range (top + 1):
		r += i
	return r ** 2
def calc_sum(top):
	r = 0
	for i in range (top):
		r += i
	return r

def calc_sum_squares(top):
	r = 0
	for i in range (top + 1):
		r += i ** 2
	return r

#for i in range(100):
print calc_squared_sum(100) - calc_sum_squares(100)

print calc_sum(15)
