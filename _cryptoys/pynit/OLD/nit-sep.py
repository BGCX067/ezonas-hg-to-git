# Echo server program
import sys
import socket
import threading
import multiprocessing
import time
import signal

from multiprocessing import Pipe, Queue, Lock
#if sys.platform != "freebsd8":
#	from Tkinter import *
### IMPORTANT PRINCIPLE WITH UDP SOCKETS:
### THIS APP CANNOT SEND DATA WITHOUT BEING ABLE TO RECEIVE !

#print socket.gethostname()

#####################
### sender thread ###
#####################	
class nit_send(threading.Thread):
	def __init__(self, stoprun, ip, port, pipe, sock, lock, peers):
		threading.Thread.__init__(self)
		if ip == None:
			self.stoprun = False
			print "NO SEND-TO ADDRESS: sender thread will terminate"
		else:
			self.stoprun = stoprun

		self.ip, self.port = ip, port
		self.sock = sock
		self.pipe = pipe
		self.lock = lock
		self.peers = peers
		print "send-to:",ip,":",port
		self.ip_port = (self.ip, self.port)


	# def run_noaddr(self):
	# 	print "sender: waiting for an address"
	# 	print self.peers
	# 	addr = self.peers[-1]
	# 	self.ip_port = (addr, self.port)
	# 	self.runf = self.run_hasaddr


	# 	self.lock.acquire()
	# 	self.lock.acquire() # will wait for a release() somewhere
	# 	print "sender stopped"
	# 	time.sleep(0.5)
	# 	print "sender: got address", addr

	def run(self):
		while self.stoprun:
			self.sock.sendto(self.pipe.recv(), self.ip_port)


#######################
### receiver thread ###
#######################
class nit_recv(threading.Thread):
	def __init__(self, stoprun, sock, peers, lock): # , ip, port):		
		threading.Thread.__init__(self)
		self.stoprun = stoprun
		self.sock = sock
		self.lock = lock
		self.peers = peers
		print "Now receiving datagram packets..."
	def run(self):
		while self.stoprun:
			data, addr = self.sock.recvfrom(1024)
			print addr[0], data
			
			if addr[0] not in self.peers:
				self.peers.append(addr[0])
				print addr[0], "added to peerlist"
				print "peers", self.peers
				if len(self.peers) == 1: # lock should have been acquired
					self.lock.release()

################
### nit node ###
################		
class nit:
	def __init__(self, argv):
		
		l = len(argv)
		ip_sendto = ""
		self.port = 10000
		print "--- PORT USED:", self.port, "---"
		self.peers = []
		##### argv managing #####
		if l in [1,2]:
			if l == 1:
				# ip_sendto = raw_input("send-to address? > ")
				ip_sendto = None
			elif l == 1 and (argv[1] == 'help' or argv[1] == '-h' or argv[1] == '--help'):
				print "args: <z|g|l|m|j>"
			else:
				ip_sendto = argv[1]
				if   ip_sendto == 'z': ip_sendto = "82.242.58.229" # home
				elif ip_sendto == 'g': ip_sendto = "212.71.19.102" # ofloo
				elif ip_sendto == 'l': ip_sendto = "localhost"
				elif ip_sendto == 'm': ip_sendto = "192.168.0.12" # moon
				elif ip_sendto == 'j': ip_sendto = "192.168.0.10" # meoo
				
				elif ip_sendto == 'qq': ip_sendto = "78.251.226.30" # meoo

		elif l == 3: # ip and port
			ip_sendto = argv[1]
			self.port = int(argv[2]) + 30000
		elif l > 3:
			sys.exit("Too many arguments")
		elif l == 0:
			print "use 'help' as arg to get help"
		self.ip_port = (socket.gethostname(), self.port)
		self.peers.append(ip_sendto)

		# we create the socket and bind it
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		# tells the socket to be reusable
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.sock.bind(self.ip_port)

		# the pipe so we can communicate with our thread
		self.pipeA, self.pipeB = Pipe()
		self.default_msg = "Oh."

		# a queue and a lock
		# self.q= Queue()
		self.lock = Lock()
		
		self.stoprun = True
		signal.signal(signal.SIGINT, self.sigint)
		
		# the sender and receiver threads
		self.nit_r = nit_recv(self.stoprun, self.sock, self.peers, self.lock)
		self.nit_s = nit_send(self.stoprun, ip_sendto, self.port, self.pipeB, self.sock, self.lock, self.peers)

		# self.nit_r.daemon = True
		# self.nit_s.daemon = True

		# print "sender alive?", self.nit_s.is_alive()
		# print "receiver alive?", self.nit_r.is_alive()
	def sigint(self, signal, frame):
		self.run = False
	def go(self):
		self.nit_r.start()
		self.nit_s.start()


		while self.stoprun:
			msg = raw_input(" > ")
			if msg == '00':
				self.sock.close()
				break
			else:
				self.pipeA.send(msg)
		# self.nit_r.terminate()
		# self.nit_s.terminate()		
		print "bye..."

n = nit(sys.argv)
n.go()



