# from multiprocessing import Lock
import multiprocessing
import threading
import socket
import time

# class thr1(multiprocessing.Process):
class sender(threading.Thread):
	def __init__(self, l):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)

	def run(self):
		while True:
			time.sleep(0.5)
			self.sock.sendto(time.ctime(time.time()), self.ip_port)
		
# class thr2(multiprocessing.Process):
class receiver(threading.Thread):
	def __init__(self, l):
		# multiprocessing.Process.__init__(self)
		threading.Thread.__init__(self)
		
	def run(self):
		while True:
			data, addr = sock.recvfrom(1024)
			print addr[0], data

		
l = [1, 2]
s = sender(l)
r = receiver(l)
port = 10000
##################################################################
ip_port = (socket.gethostname(), port)
# we create the socket and bind it
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(ip_port)

r.sock = sock
s.sock = sock
s.ip_port = ("127.0.0.1", 10000)


r.start()
# print "alive ?",  t1.is_alive()
time.sleep(0.2)
s.start()
s.join()
r.join()

