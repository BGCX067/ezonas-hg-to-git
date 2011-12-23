#!/usr/bin/env python
# ezjonas@gmail.com

import sys
import math

def dividers(n):
	result = [1, n]
	for a in range(2, n/2+1):
		if n % a == 0:
			result.append(a)
	return result

def how_many_dividers(n):
	result = 0
	lim = int(math.sqrt(n))
	i = n
	candidate = 1
	while candidate <= lim:
		if n % candidate == 0:
			result += 2
		candidate += 1
	return result
	
# print len(dividers(432432))
# print how_many_dividers(432432)

if len(sys.argv) == 2:
	triangle = 0
	i = 0
	step = 200
	limit = int(sys.argv[1])
	for a in range(1, limit):
	
		triangle += a
		# print "+", a, "=", triangle

		i += 1
		if i % step == 0:
			print i, triangle

		# print triangle, len(dividers(triangle))

		thing = how_many_dividers(triangle)
		# thing = len(dividers(triangle))
		if thing > 100:
			print i, triangle, "has", thing, "dividers"
		if thing > 500:
			break
	print triangle
