# Echo server program
import sys
import os
import socket
import threading
import multiprocessing
import time
import signal

from multiprocessing import Pipe, Queue#, Lock
#if sys.platform != "freebsd8":
#	from Tkinter import *
### IMPORTANT PRINCIPLE WITH UDP SOCKETS:
### THIS APP CANNOT SEND DATA WITHOUT BEING ABLE TO RECEIVE !

#print socket.gethostname()

###############################################################
### sender thread #############################################
###############################################################
class nit_send(threading.Thread):
	
	def __init__(self,
			stoprun,
			ip_port, pipe,
			sock, peers):
		self.runs = False
		threading.Thread.__init__(self)
		self.stoprun = stoprun
		self.hasaddr = None
		self.sock = sock
		self.pipe = pipe
		self.peers = peers
		
		print "[send]", ip_port
		self.ip_port = ip_port # (self.ip, self.port)

	def set_ip_port(self, ip_port):
		self.ip_port = ip_port
		print "[send] ip_port set to", self.ip_port
		
	def set_recv(self, recver): self.recver = recver

	def run(self): ### WHILE LOOP ###########################		

		print "[send] SEND LOOP STARTED !"
		self.runs = True
		while self.stoprun and self.hasaddr:
			self.sock.sendto(self.pipe.recv(), self.ip_port)
		print "[send] send thread exited"
		print "[send] note: hasaddr =", self.hasaddr


#################################################################
### receiver thread #############################################
#################################################################

class nit_recv(threading.Thread):
	def __init__(self,
			stoprun,
			sock,
			peers):
			# , ip, port):
		threading.Thread.__init__(self)
		self.stoprun = stoprun
		self.sock = sock
		self.peers = peers
		print "[recv] Now receiving datagram packets..."

	def set_send(self, sender):	self.sender = sender

	def set_runstop(self, val):
		self.runstop = val
	def set_hasaddr(self, val):
		self.hasaddr = val
	def run(self):
		while self.stoprun:
			data, addr = self.sock.recvfrom(1024)
			print addr[0], data
			
			if addr[0] not in self.peers:
				self.sender.set_ip_port((addr[0], 10000))
				self.peers.append(addr[0])
				self.sender.hasaddr = True
				print "[recv]", addr[0], "added to peerlist"
				print "peers: ", self.peers
		print "[recv] recv thread exited"

##########################################################
### nit node #############################################
##########################################################
class nit(threading.Thread):
	def __init__(self, argv):
		threading.Thread.__init__(self)
		l = len(argv)
		ip_sendto = ""
		self.port = 10000
		print "[NIT] PORT USED:", self.port
		self.peers = []
		self.hasaddr = False
		# print "seems my ip is", os.popen("curl curlmyip.com").readline()
		if l > 3:
			sys.exit("Too many arguments")
		elif l == 1:
			ip_sendto = None
			print "args: <z|g|l|m|j>"
		elif l == 2:
			ip_sendto = argv[1]
			if ip_sendto != None:
				if   ip_sendto == 'z': ip_sendto = "82.242.58.229"
				elif ip_sendto == 'g': ip_sendto = "212.71.19.102"
				elif ip_sendto == 'qq': ip_sendto = "78.251.229.79"
				else:
					sys.exit("[NIT] invalid addr argument !")

				self.hasaddr = True
				self.peers.append(ip_sendto)
			else:
				self.hasaddr = False
				
			self.nit_s.hasaddr = self.hasaddr
		##########################################################
		### network sockets and shoes and underpants and pipes ###
		##########################################################
		self.ip_port = (socket.gethostname(), self.port)

		# we create the socket and bind it
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		# tells the socket to be reusable
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.sock.bind(self.ip_port)

		# the pipe so we can communicate with our thread
		self.pipeA, self.pipeB = Pipe()
		
		self.stoprun = True
		# signal.signal(signal.SIGINT, self.sigint)
		
		# the sender and receiver threads
		self.nit_r = nit_recv(self.sock, self.peers)
		self.nit_s = nit_send(
			(ip_sendto, self.port),
			self.pipeB,
			self.sock,
			self.peers)
		
	def run(self):
		self.nit_r.set_send(self.nit_s)
		self.nit_s.set_recv(self.nit_r)

		self.nit_r.start()

		while self.stoprun:
			if self.hasaddr:
				if not self.nit_s.runs:
					self.nit_s.start()
				msg = raw_input(" > ")
				if msg == '00':
					self.sock.close()
					self.stoprun = False
					break
				else:
					self.pipeA.send(msg)

			else:
				raw_input("<[NIT] #@%@#@%@# NO-ADDR #@%@#@%@# !>")

		# self.nit_r.terminate()
		# self.nit_s.terminate()		
		print "bye..."

n = nit(sys.argv)
n.start()

### RUNS ? hasaddr ? LOL !


