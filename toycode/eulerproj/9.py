#!/usr/bin/env python
# ezjonas@gmail.com
import sys
limit = 500
for a in range(limit):
	for b in range(a+1, limit):
		for c in range(b+1, limit):
			if a*a + b*b == c*c and a + b + c == 1000:
				print a,b,c
				print a*b*c
				sys.exit(0)