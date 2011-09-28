class c:
	def f(self,l):
		self.l = l
		self.l.append(2)
	
l = [23, 47]

cc = c()
cc.f(l)

print l