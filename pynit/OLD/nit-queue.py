# Echo server program
import sys
import socket
import threading
import multiprocessing
from multiprocessing import Pipe, Queue
if sys.platform != "freebsd8":
	from Tkinter import *

#print socket.gethostname()

#################################################################
### receiver thread #############################################
#################################################################
class nit_recv(multiprocessing.Process):
	def __init__(self, sock): # , ip, port):		
		multiprocessing.Process.__init__(self)		
		self.s = sock
		self.peers = []
		print "receiver created"
	def run(self):
		while 1:
			data, addr = self.s.recvfrom(1024) ### BLOCKS ! ###
			print addr, data

#################################################################
### sender thread ###############################################
#################################################################		
class nit_send(multiprocessing.Process):
	#def __init__(self, ip, port, pipe, sock):
	def __init__(self, ip, port, q, sock):
		multiprocessing.Process.__init__(self)
		self.ip_port = (ip, port)
		print "send-to addr:",ip,":",port
		self.s = sock
		self.q = q
		#self.pipe = pipe
	def run(self):
		while 1:
			#self.s.sendto(self.pipe.recv(), self.ip_port) ### BLOCKS ! ###
			data = self.q.get()
			print "will send", data
			self.s.sendto(data, self.ip_port) ### BLOCKS ! ###
			#self.join()

#################################################################
### nit node ####################################################
#################################################################		
class nit:
	def __init__(self, argv):
		
		l = len(argv)
		ip_sendto = ""
		self.port = 30001
		##### argv managing #####
		if l == 1:
			ip_sendto = raw_input("Type send-to address\n > ")
			if ip_sendto == 'z':
				ip_sendto = "82.242.58.229"
			if ip_sendto == 'g':
				ip_sendto = "spark.ofloo.net"
		elif l == 2: # just the ip
			ip_sendto = argv[1]
		elif l == 3: # ip and port
			ip_sendto = argv[1]
			self.port = int(argv[2]) + 30000
		elif l > 3:
			sys.exit("Too many arguments")

		self.ip = socket.gethostname()
		self.ip_port = (self.ip, self.port)

		# we create the socket and bind it
		self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		# tells the socket to be reusable
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.s.bind(self.ip_port)
		# the pipe so we can communicate with our thread
		#self.pipeA, self.pipeB = Queue()
		self.q = Queue()
		self.default_msg = "Dou I wanna ya ass'" ### duh
		self.nit_r = nit_recv(self.s)

		#self.nit_s = nit_send(ip_sendto, self.port, self.pipeB, self.s)
		self.nit_s = nit_send(ip_sendto, self.port, self.q, self.s)
		self.nit_r.start()
		self.nit_s.start()

		# from here we check if it's a daemon styled server or a desktop #

		if sys.platform != "freebsd8": ### my server I was using
			self.root = Tk()
			frame = Frame(self.root)
			frame.pack()
			button = Button(frame, text="QUIT", fg="red", command=frame.quit)
			button.pack(side=LEFT)
			hi_there = Button(frame, text="send", command=self.sendmsg)
			hi_there.pack(side=LEFT)
		#print "sender alive?", nit_s.is_alive()
		#print "receiver alive?", nit_r.is_alive()
	def sendmsg(self):
		#self.pipeA.send(self.default_msg)
		self.q.put(self.default_msg)
	def go(self):
		#if sys.platform != "freebsd8":
			#self.root.mainloop()
		#else:
		while True:
			#self.pipeA.send(raw_input("Type a message to send:\n > "))
			self.q.put(raw_input("Type a message to send:\n > "))
			#self.nit_s.join()
##############################################################

n = nit(sys.argv)
n.go()







