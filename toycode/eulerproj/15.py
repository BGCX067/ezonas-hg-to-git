#!/usr/bin/env python
# ezjonas@gmail.com

def fact(n):
	if n == 1:
		return 1
	else:
		return fact(n-1) * n
		
# print fact (100)
result = 0
for a in str(fact (100)):
	result += int (a)
print result