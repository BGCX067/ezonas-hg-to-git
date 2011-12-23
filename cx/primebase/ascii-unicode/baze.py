import sys
def z(n, base):
	if base < 2:
		return "bad base"
	exp = 0
	while n > base ** exp:
		exp += 1
	result = []
	rest = n
	while exp >= 0:
		if n >= base ** exp:
			result.append(rest / base ** exp)
			rest %= base ** exp
		exp -= 1
	return result
	
def y(digits, base):
	result = 0
	exp = len (digits) - 1
	for d in digits:
		result += d * (base ** exp)
		exp -= 1
	return result
		
		
print y([2, 0], 16)
print y([2, 1], 16)

print z(257, 23)