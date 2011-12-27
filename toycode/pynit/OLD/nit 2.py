# Echo server program
import sys
import socket
import threading
import multiprocessing
from multiprocessing import Pipe, Queue
#if sys.platform != "freebsd8":
#	from Tkinter import *

#print socket.gethostname()

#######################
### receiver thread ###
#######################
class nit_recv(multiprocessing.Process):
	def __init__(self, sock, peers): # , ip, port):		
		multiprocessing.Process.__init__(self)		
		self.s = sock
		self.peers = peers
		print "receiver created"
	def run(self):
		while 1:
			data, addr = self.s.recvfrom(1024) ### BLOCKS ! ###
			if addr[0] not in self.peers:
				self.peers.append(addr[0])
			print addr[0], addr[1], data

#####################
### sender thread ###
#####################	
class nit_send(multiprocessing.Process):
	#def __init__(self, ip, port, pipe, sock):
	def __init__(self, ip, port, q, sock):
		multiprocessing.Process.__init__(self)
		self.ip_port = (ip, port)
		print "send-to addr:",ip,":",port
		self.s = sock
		#self.q = q
		self.pipe = q
	def run(self):
		while 1:
			data = self.pipe.recv()
			self.s.sendto(self.pipe.recv(), self.ip_port) ### BLOCKS ! ###

################
### nit node ###
################		
class nit:
	def __init__(self, argv):
		
		l = len(argv)
		ip_sendto = ""
		self.port = 10000
		##### argv managing #####
		if l == 1 or l == 2:
			if l == 1:
				ip_sendto = raw_input("Type send-to address\n > ")
			else:
				ip_sendto = argv[1]
				if ip_sendto == 'z':
					ip_sendto = "82.242.58.229"
				elif ip_sendto == 'g':
					ip_sendto = "212.71.19.102"
				elif ip_sendto == 'w':
					ip_sendto = "78.251.249.185"
				elif ip_sendto == 'l':
					ip_sendto = "localhost"
				elif ip_sendto == 'm':
					ip_sendto = "192.168.0.12"
				elif ip_sendto == 'j':
					ip_sendto = "192.168.0.10"

		elif l == 3: # ip and port
			ip_sendto = argv[1]
			self.port = int(argv[2]) + 30000
		elif l > 3:
			sys.exit("Too many arguments")

		self.ip = socket.gethostname()
		self.ip_port = (self.ip, self.port)
		self.peers = []
		# we create the socket and bind it
		self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		# tells the socket to be reusable
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.s.bind(self.ip_port)
		# the pipe so we can communicate with our thread
		self.pipeA, self.pipeB = Pipe()
		self.default_msg = "Dou I wanna ya ass'" ### duh
		self.nit_r = nit_recv(self.s, self.peers)
		self.nit_s = nit_send(ip_sendto, self.port, self.pipeB, self.s)

		#print "sender alive?", self.nit_s.is_alive()
		#print "receiver alive?", self.nit_r.is_alive()
		
	def go(self):
		self.nit_r.start()
		self.nit_s.start()
		# if sys.platform != "freebsd8":
		# 	self.root.mainloop()
		# else:
		while True:
			msg = raw_input("send?\n > ")
			#print "sending to pipe:", msg
			self.pipeA.send(msg)
				#self.q.put(raw_input("Type a message to send:\n > "))
				#self.nit_s.join()
##############################################################

n = nit(sys.argv)
n.go()







