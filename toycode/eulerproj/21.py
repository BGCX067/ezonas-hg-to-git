#!/usr/bin/env python
# ezjonas@gmail.com

def dividers(n):
	result = [1]
	for a in range(2, n/2+1):
		if n % a == 0:
			result.append(a)
	return result


def amical(n):
	s = sum(dividers(n))
	if s == n:
		return 0
	if n == sum(dividers(s)):
		return s
	else:
		return 0

r = []
for a in range(10000):
	t = amical (a)
	if t != 0:
		print a, t
		r.append(a)
		r.append(t)
		
print sum(set(r))
print set(r)
		