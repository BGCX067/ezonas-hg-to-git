f = open("ff-normed.txt")

words = []
results = []
for a in f.readlines():
    if len(a[:-1]) == 6:
        words.append(a[:-1])
for a in words:
    for b in words:
        if a[1:] == b[1:] and a != b:
            results.append([a, b])

res = open("results-sim.txt", "w")
for d in results:
    res.write(d[0] +" "+ d[1]+"\n")
