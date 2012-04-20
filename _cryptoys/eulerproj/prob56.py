r = 0
for a in range(100):
	for b in range(100):
		s = str(a**b)
		t = 0
		for c in s:
			t += int(c)
		if t > r:
			r = t
print r
