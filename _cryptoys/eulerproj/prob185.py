import copy

d = {
"5616185650518293" : 2,
"3847439647293047" : 1,
"5855462940810587" : 3,
"9742855507068353" : 3,
"4296849643607543" : 3,
"3174248439465858" : 1,
"4513559094146117" : 2,
"7890971548908067" : 3,
"8157356344118483" : 1,
"2615250744386899" : 2,
"8690095851526254" : 3,
"6375711915077050" : 1,
"6913859173121360" : 1,
"6442889055042768" : 2,
"2321386104303845" : 0,
"2326509471271448" : 2,
"5251583379644322" : 2,
"1748270476758276" : 3,
"4895722652190306" : 1,
"3041631117224635" : 3,
"1841236454324589" : 3,
"2659862637316867" : 2 
}
l = []
corrects = []
for key in d:
	# print key, d[key]
	l.append(list(key))
	corrects.append(d[key])
print len(d), "items"

l2 = copy.deepcopy(l)

marks = 22*[16*[0]]
marks0 = 22*[16*[1]]

strlen = len(l[0])
sz = len(l)

# for e in range(sz):						# main pointer
# 	for cross in range(e, sz):			# child pointer
# 		for n in range(strlen):
# 			if l[cross][n] == l[e][n]:
# 				l2[e][n] = ' '

print ("///////// STEP 1 /////////")

for e in range(sz):						# main pointer
	for n in range(strlen):
		if l[14][n] == l[e][n]:
			l2[e][n] = 'X'
			marks0[e][n] = 0
for a in l2:
	print ''.join(a), '.'

print ("///////// STEP 2 /////////")

for e in range(sz):						# main pointer
	for f in range(e, sz):			# child pointer
		for n in range(strlen):
			if l[f][n] != l[e][n]:
				if marks0[f][n] == 1:
					marks[f][n] += 1
for a in range(22):
	for b in range(16):
		if marks[a][b] != '1':
			l2[a][b] = ' '
for a in marks0:
	print a

for a in marks:
	print a
	# print ''.join(a), '.'
# for a in l2:
# 	print ''.join(a), '.'


		
