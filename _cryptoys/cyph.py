counters = {}

string = 'SMVRDZ OHJJHYZVU ZDNG, "NS NZ UHNSMHY THDQSM UVY ZWQHUGVY ELS SYDUXLNQNSB DUG\
 VFFLWDSNVU, TMNFM KNIH MDWWNUHZZ." HUIB MNR!'

# 
# 
# 
# 
# 
# 
# 
# f = open("words1000.html")

f = open("words1000.html")
f2 = open("results1000.txt", 'w')
# f = open("words100.txt")
# f2 = open("results100.txt", 'w')
content = f.read()
lenghts = {}
for a in range(10):
    lenghts[a] = []
for a in sorted(content.split(' ')):
    lenghts[len(a)].append(a)

for k, v in lenghts.iteritems():
    if len(v) != 0:
        s = ''
        for a in v:
            s += a + ' '
        print "--- words with", k, "letters ---"
        print s
        f2.write("--- words with " + str(k) + " letters ---\n")
        f2.write(s+'\n')

    
# for a in sorted(s.split(' ')):
#     print a
# or a in string:
#    counters[a] = 0
#  print counters
# or a in string:
#    counters[a] += 1
#  print counters
# or k, v in counters.iteritems():
#    s = ''
#    if v > 7 and k != ' ':
#        for fd in range(v):
#            s+='#'
#        print k, v, '\t', s
# 


# E T A O I N S H
# am an as at be by do go he if in is it me my no of oh on or so to up us we 
# act add age ago air all and any are ask bed big box boy but can car cry cut day did dog dry eat end eye far few fly for get got had has her him his hot hot how lay lot low man map may men new now off old one our out own put ran red run saw say sea see set she sit six sun ten the too top try two use war was way who why yes yet you 

#
#
#
#
#
#
# e	12.702%	
# t	9.056%	
# a	8.167%	
# o	7.507%	
# i	6.966%	
# n	6.749%	
# s	6.327%	
# h	6.094%	
# r	5.987%	
 

# ordered = {}
# counts = []
# for k, v in counters.iteritems():
    # counts.append(v)
    # ordered[v] = k
# counts.sort()

# for a in counts:
    # print a, ordered[a]