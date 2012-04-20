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
class nit_recv(threading.Thread):
	def __init__(self, sock, peers): # , ip, port):		
		threading.Thread.__init__(self)		
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
class nit_send(threading.Thread):
	def __init__(self, ip, port, pipe, sock):
		threading.Thread.__init__(self)
		self.ip_port = (ip, port)
		print "send-to addr:",ip,":",port
		self.s = sock
		self.pipe = pipe
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
		if l == 1:
			ip_sendto = raw_input("Type send-to address\n > ")
		elif l == 2: # just the ip
			ip_sendto = argv[1]
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
		self.default_msg = "Just a default message"

		self.nit_r = nit_recv(self.s, self.peers)
		self.nit_s = nit_send(ip_sendto, self.port, self.pipeB, self.s)

		self.nit_r.start()
		self.nit_s.start()
		
	def go(self):
		while True:
			msg = raw_input("send?\n > ")
			self.pipeA.send(msg)

n = nit(sys.argv)
n.go()







