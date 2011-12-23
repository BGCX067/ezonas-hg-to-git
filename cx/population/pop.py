import os

data = {0.2: 453, -4:23, 200: 43}

file = open("pop.txt", "w")
for key in data:
	file.write(str(key)+" "+str(data[key])+"\n")

os.popen("gnuplot -e \"plot \\\"pop.txt\\\" using 1:2\"")


file.close()

