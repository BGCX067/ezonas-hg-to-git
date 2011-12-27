#!/usr/bin/env python
# ezjonas@gmail.com
f = open("prime2-e-6.txt")
primes = []
for a in f.readlines():
	primes.append(int(a))
	
result = 0
for a in primes:
	result += a
print result