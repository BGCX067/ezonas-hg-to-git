from multiprocessing import Lock
import threading
import time
class thr1(threading.Thread):
	def __init__(self, lock):
		threading.Thread.__init__(self)
		self.lock = lock
	def run(self):
		lock.acquire()
		for a in range(10):
			print "Hello chicken, welcome egg"
			time.sleep(0.1)
			lock.acquire()
	def stop(self):
		self._stop.set()
class thr2(threading.Thread):
	def __init__(self, l):
		threading.Thread.__init__(self)
	def run(self):
		pass
		
# lock: blocks when acquire(), continues when release()
lock = Lock()
thr = thr1(lock)
thr.start()
b = 2
for a in range(5):
	time.sleep(0.5)
	b *= a
	print "time to hatch, egg !", a
	lock.release()
	
thr1.stop()