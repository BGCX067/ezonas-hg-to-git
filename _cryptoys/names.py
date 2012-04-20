b = open("names-result.txt", "w")
for a in open("names.txt").readlines():
	if len(a) < 30:
		b.write(a)
		
	
		
		


b.close()

	