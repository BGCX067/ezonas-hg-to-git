def combinations(n): # C 2 n = n! / (2!(n - 2)!)
	return n*(n-1)/2

def calculate(i, n):
	if i <= 0:
		return n
	r = calculate(i-1, n)
	return r + combinations(r)

	
def int32size(n):
	return n*4
print calculate(1, 10)
print calculate(2, 10)
print calculate(3, 10)
	
	
