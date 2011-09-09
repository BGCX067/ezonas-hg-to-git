import multiprocessing
from multiprocessing import Lock
import threading
import time
import signal

class thr1(threading.Thread):
# class thr1(multiprocessing.Process):
	def __init__(self, l):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)
		self.l = l
		#signal.signal(signal.SIGINT, self.sigint)
		
	def run(self):
		b = True
		try:
			self.l.append(3)
			for a in range(100):
				# time.sleep(0.5)
				raw_input("fdsfsd")
				print "dih"
				if b == False:
					break
		except KeyboardInterrupt:
			print "doh"
			b = False
	def sigint(self, signal, frame):
		print "duh !"
		

l = [34, 534]

thr = thr1(l)
thr.start()

print l

# thr1.terminate()