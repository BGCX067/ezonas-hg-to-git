import sys
import os

# print sys.argv[1]
# print os.popen("./basex.out s " + sys.argv[1]).readline()# " | ./factorize.out").readline()

# if(len(sys.argv) > 0):
# 	print sys.argv[1], '=', os.popen("./basex.out \"" + sys.argv[1]+ "\" | ./factorize.out").read(),
# else:	
if(len(sys.argv) > 0):
	for a in open(sys.argv[1]).readlines():
		# for i in a: print ord(i)
		print a[:-2], '=', os.popen("./basex.out \"" + a + "\" | ./factorize.out").read(),