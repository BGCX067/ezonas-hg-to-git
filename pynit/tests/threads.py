# from multiprocessing import Lock
import multiprocessing
import threading
import time

# class thr1(multiprocessing.Process):
class thr1(threading.Thread):
	def __init__(self, l, flag):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)
		self.l = l
		self.l.append('t1')
		self.flag = flag
		# print "[1i]", self.l
	def run(self):
		self.l.append("t1r")
		print "[1r]", self.l, self.flag
	# def show(self):
	# 	print "[1]", self.l
		
# class thr2(multiprocessing.Process):
class thr2(threading.Thread):
	def __init__(self, l, flag):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)
		self.l = l
		self.l.append('t2')
		self.flag = flag
		# print "[2i]", self.l, self
		
	def run(self):
		self.l.append("t2r")
		print "[2r]", self.l, self.flag
	# def show(self):
	# 	print "[2]", self.l
		
l = [1, 2]
t1 = thr1(l, True)
t2 = thr2(l, True)
l.append(3)

t1.start()

t2.start()
time.sleep(0.2)

print "alive ?",  t2.is_alive()

t2.start()
