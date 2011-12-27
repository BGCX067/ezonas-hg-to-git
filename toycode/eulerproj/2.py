l = [0, 1]
while l[-1] < 4000000:
	l.append(l[-1] + l[-2])
result = 0
for a in l:
	if a % 2 == 0:
		result += a
print result