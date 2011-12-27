def power_friend(m, n):
	print n**m * m**n
	
power_friend (2, 2)

l = (2, 3, 5, 7, 11, 13, 17, 19)
for i in l:
	for j in l:
		power_friend(i,j)