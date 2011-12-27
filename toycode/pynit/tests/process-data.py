import multiprocessing
from multiprocessing import Lock, Pipe
import threading
import time
import signal

class thr1(threading.Thread):
# class thr1(multiprocessing.Process):
	def __init__(self, l, pipe):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)
		self.l = l
		self.pipe = pipe
		#signal.signal(signal.SIGINT, self.sigint)
		
	def run(self):
		i = ""
		self.l.append(3)
		self.l.append(self.pipe.recv())
		
		for a in range(100):
			# time.sleep(0.5)
			i = raw_input("fdsfsd")
			if i == "00":
				print "doh"
				break
			print "dih"
		# except KeyboardInterrupt: # DUH DOZNT WURQ
				
	def sigint(self, signal, frame):
		print "duh !"
		

l = [34, 534]
pipeA, pipeB = Pipe()
thr = thr1(l, pipeA)
thr.start()

pipeB.send("Hellow")

print l

# thr1.terminate()