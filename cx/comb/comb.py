import math
def fact(n):
	if n == 2:
		return 2
	return fact(n - 1) * n
	
def comb(n, k):
	if n < k:
		return '.'
	return math.factorial(n) / (math.factorial(k) * math.factorial(n-k))

def perm(n, k):
	if n < k:
		return -1
	return math.factorial(n) / math.factorial(n-k)

def to_html(limit, char = '\t'):
	print "combinations"
	print "<table>"
	header = "<tr>"
	for i in range(2,limit):
		header += "<td>" + str(i) + "</td>"
	print header + "</tr>"
	for i in range(2,limit):
		line = "<tr>" + "<td>" + str(i) +  "</td>"
		for j in range(2,limit):
			line += "<td>" + str(comb(i, j)) + "</td>"
		print line + "</tr>"
	print "</table>"

def to_html2(limit, char = '\t'):
	print "combinations"
	print "<table>"
	header = "<tr>"
	for i in range(2,limit):
		header += "<td>" + str(i) + "</td>"
	print header + "</tr>"
	for i in range(2,limit):
		line = "<tr>" + "<td>" + str(i) +  "</td>"
		for j in range(2,limit):
			line += "<td>" + str(comb(j, i)) + "</td>"
		print line + "</tr>"
	print "</table>"

to_html2(20)