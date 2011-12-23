#!/usr/bin/env python
# ezjonas@gmail.com
a, b = 0, 0
for i in range(101):
	a += i
	b += i * i

a *= a
print a- b