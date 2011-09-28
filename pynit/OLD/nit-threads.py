# Echo server program
import sys
import socket
import threading
import multiprocessing
from multiprocessing import Pipe
if sys.platform != "freebsd8":
	from Tkinter import *

#print socket.gethostname()

#################################################################
### receiver thread #############################################
#################################################################
class nit_recv(threading.Thread):
	def __init__(self, sock): # , ip, port):		
		threading.Thread.__init__(self)		
		self.s = sock
		self.peers = []
	def run(self):
		while 1:
			data, addr = self.s.recvfrom(1024)
			if addr not in self.peers:
				self.peers.append(addr)
			#if data == None:
			#	break
			print "received:",data," from ",addr
			#self.s.sendto("received"+data, 0, self.ip_port)

#################################################################
### sender thread ###############################################
#################################################################		
class nit_send(threading.Thread):
	def __init__(self, ip, port, pipe, sock):
		threading.Thread.__init__(self)
		self.ip_port = (ip, port)
		print "send-to addr:",ip,":",port
		self.s = sock
		self.pipe = pipe
	def run(self):
		self.s.sendto(self.pipe.recv(), self.ip_port)

#################################################################
### nit node ####################################################
#################################################################		
class nit:
	def __init__(self, argv):
		
		l = len(argv)
		ip_sendto = ""
		self.port = 30000 # port will stay 30k for now
		##### argv managing #####
		if l == 1:
			ip_sendto = raw_input("Type send-to address\n > ")
			if ip_sendto == 'zz':
				ip_sendto = "82.242.58.229"
			#if iphost == "" or iphost == 'n':
				#sys.exit("Using no ip address")
		elif l == 2: # just the ip
			ip_sendto = argv[1]
		elif l == 3: # ip and port
			ip_sendto = argv[1]
			port = argv[2]
		elif l > 3:
			sys.exit("Too many arguments")

		self.ip = socket.gethostname()
		self.ip_port = (self.ip, self.port)

		### we create the socket and bind it
		self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		### tells the socket to be reusable
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.s.bind(self.ip_port)
		### the pipe so we can communicate with our thread
		self.pipeA, self.pipeB = Pipe()
		self.default_msg = "Dou I wanna ya ass'" ### duh
		self.nit_r = nit_recv(self.s)
		if ip_sendto == "" or ip_sendto == 'n':
			print "No valid send-to address, not sending"
		else:
			self.nit_s = nit_send(ip_sendto, self.port, self.pipeB, self.s)
			
		self.nit_r.start()
		if ip_sendto != "" and ip_sendto != 'n':
			self.nit_s.start()

		
		######################################################################
		### from here we check if it's a daemon styled server or a desktop ###
		######################################################################
		if sys.platform != "freebsd8": ### my server I was using
			self.root = Tk() ## so here we are a desktop, note the "!=" in the previous line
			frame = Frame(self.root)
			frame.pack()
			button = Button(frame, text="QUIT", fg="red", command=frame.quit)
			button.pack(side=LEFT)

			hi_there = Button(frame, text="send", command=self.sendmsg)
			hi_there.pack(side=LEFT)

	def sendmsg(self):
		self.pipeA.send(self.default_msg)
		#self.nit_s.join()
		self.nit_r.join()
	def go(self):
		if sys.platform != "freebsd8":
			self.root.mainloop()
		else:
			while True:
				self.pipeA.send(raw_input("Type a message to send:\n > "))
				#self.nit_s.join()
				self.nit_r.join()
##############################################################

n = nit(sys.argv)
n.go()







