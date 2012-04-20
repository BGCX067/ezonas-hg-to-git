b = open("names-result2.txt", "w")
s = set()
for a in open("names-result.txt").readlines():
	s.add(a)
	
		
		

for a in s:
	b.write(a)
b.close()

	