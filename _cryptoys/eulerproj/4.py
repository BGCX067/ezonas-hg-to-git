largest = 0
for a in range(100, 1000):
	for b in range(100, 1000):
		s = str(a * b)
		if s[0] != s[-1]: continue
		if s[1] != s[-2]: continue
		if s[2] != s[-3]: continue
		if a * b > largest:
			largest = a * b

print largest