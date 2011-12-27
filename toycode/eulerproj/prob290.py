count = 0

def calc(n):
	numbs = map(int, str(n))
	return sum(numbs)

i = 0

while i < 10 ** 18:
	i += 1
print "done"
i = 0
while i < 10 ** 18:

	if calc(i) == calc(137 * i):
		count += 1

	i+=1

#print calc (1234)
print count
