# Echo server program
import sys, socket, threading, time, signal
# os, multiprocessing
# from multiprocessing import Pipe, Queue#, Lock

### RECEIVER ### RECEIVER ### RECEIVER ### RECEIVER ### RECEIVER ###
class nit_recv(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self)
		self.runs = True
		# signal.signal(signal.SIGINT, self.sighandle)

	def run(self):
		print "[RECV] LOOP STARTED !"
		while self.runs == True:
			data, addr = self.sock.recvfrom(1024)
			if data == '00':
				print "[RECV] received shutdown datagram"
				# self.sock.sendto('00', addr)
				self.sock.sendto('00', (socket.gethostname(), 10000))
				self.runs = False
			print time.ctime(time.time()), addr[0], data
			if addr[0] not in self.peers:
				self.send.ip_port = (addr[0], 10000)
				self.peers.append(addr[0])
				print "[RECV]", addr[0], "added to peerlist"
		print "[RECV] end"
	# def sighandle(self, signum, frame):
	# 	sys.exit("SIGINT")
		
### SENDER ### SENDER ### SENDER ### SENDER ### SENDER ### SENDER ###
class nit_send(threading.Thread):

	def __init__(self):
		threading.Thread.__init__(self)
		self.runs = False
	def run(self):
		print "[SEND] loop started"
		print "[SEND] sending to", self.ip_port
		input = "I don't even"
		while self.runs == True:
			try:
				input = raw_input(" > ")
			except:
				self.runs = False
				
			if input == '00':
				self.runs = False
				self.sock.sendto(input, (socket.gethostname(), 10000))
			self.sock.sendto(input, self.ip_port)
		print "[SEND] end"
	# def sighandle(self, signum, frame):
	# 	self.runs = False
	# 	print "[SEND] captured SIGINT"
	# 	sys.exit("SIGINT")
		

### MAIN ### MAIN ### MAIN ### MAIN ### MAIN ### MAIN ### MAIN ### MAIN ###
class nit(threading.Thread):
	def __init__(self, argv):
		threading.Thread.__init__(self)
		
		l = len(argv)
		ip_sendto = ""
		self.port = 10000
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
				elif ip_sendto == 'l': ip_sendto = socket.gethostname()
				elif ip_sendto == 'g': ip_sendto = "212.71.19.102"
				elif ip_sendto == 'gg': ip_sendto = "212.71.19.103"
				elif ip_sendto == 'qq': ip_sendto = "78.251.229.224"
				else: sys.exit("[NIT] invalid addr argument !")

				self.hasaddr = True
				self.peers.append(ip_sendto)
				
		### network sockets and shoes and underpants and pipes ###

		self.ip_port = (socket.gethostname(), self.port)
		# we create the socket and bind it
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 		# tells the socket to be reusable
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.sock.bind(self.ip_port)

		### the sender and receiver threads ###
		self.nit_r = nit_recv()
		self.nit_s = nit_send()
		self.nit_r.peers = self.peers
		self.nit_r.sock = self.sock
		self.nit_s.sock = self.sock
		self.nit_s.ip_port = (ip_sendto, self.port)
		print self.nit_s.ip_port
		self.nit_r.send = self.nit_r
		self.nit_s.recv = self.nit_s
		
		self.nit_r.runs = True
		if self.hasaddr == True:
			self.nit_s.runs = True
			self.nit_s.hasaddr = True
		
	def run(self):
		self.nit_r.start()
		time.sleep(0.3)
		if self.nit_s.runs == True:
			self.nit_s.start()
		self.nit_r.join()
		self.nit_s.join()
		print "[NIT] end"
		# self.sock.shutdown(socket.SHUT_RDWR)		
		self.sock.close()		

n = nit(sys.argv)
n.start()

### RUNS ? hasaddr ? LOL !


