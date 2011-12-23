#!/usr/bin/env python
# ezjonas@gmail.com

limit = 10**1000

l = [0, 1]
# while l[-1] <= limit:
while len(str(l[-1])) <= 1000:
	l.append(l[-1]+l[-2])
print len(l)
for a in l:
	print len(str(a)), a
# print l[-1]
