#!/usr/bin/env python
# ezjonas@gmail.com

import sys

def collatz(n):
	# result = [n]
	result = 1
	while n != 1:
		if n % 2 == 0:
			n /= 2
		else:
			n = 3 * n + 1
		result += 1
	return result
		
# if len(sys.argv) != 2:
# 	sys.exit("needs an argument")

i = 1000000
max = 0
step = 10000
cand = 0
solution = 0

while i > 1:
	cand = collatz(i)
	if cand > max:
		max = cand
		solution = i
	i -= 1
	if i % step == 0:
		print i
print cand, solution