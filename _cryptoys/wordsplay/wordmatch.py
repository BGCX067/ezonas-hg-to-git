f = open("words-nix")

#print f.readlines()
f2 = open("words6.txt", 'w')
words = []
for a in f.readlines():
    if len(a) == 7:
        if a[0] == a[5]:
            words.append(a)

for a in words:
    f2.write(a)