f = open("f.txt")

ar = f.read().split(',')
ar[-1] = '73'
ar = map(int, ar)
print "size:", len(ar)

# def genkeys():
# 	ls = []
# 	key = [97, 97, 97]
# 	ls.append(key)
# 	a, z = ord('a'), ord('z')
# 	while True:
# 		key[2] += 1
# 		if key[2] > z:
# 			key[1] += 1
# 			key[2] = a
# 			if key[1] > z:
# 				key[0] += 1
# 				key[1] = a
# 				key[2] = a
# 				if key[0] > z:
# 					break

a, z = ord('a'), ord('z')

for l in range(a, z+1):
	for m in range(a, z+1):
		for n in range(a, z+1):
			k = [l, m, n]
			text = ""
			for w in range(4):
			#for w in range(len(ar)):
				text += chr (ar[w] ^ k[w%3])
			if text == "(The":
				print chr(l), chr(m), chr(n)
				sol = 0
				for w in range(len(ar)):
					sol += ar[w] ^ k[w%3]
				print sol
			#print text



		#print key
		#ls.append (list(key))
	#print ls
	#return ls

#keyring = genkeys()
#print genkeys()
#for w in range(len(ar)):
#for k in keyring:






