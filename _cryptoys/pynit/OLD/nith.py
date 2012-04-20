class nit:
	def __init__(self, argv):
		l = len(argv)
		iphost = ""
		port = 30000 # port will stay 30k for now
		if l == 1:
			iphost = raw_input("Type hostname or IP internet address\n > ")
			#if iphost == "" or iphost == 'n':
				#sys.exit("Using no ip address")
		elif l == 2: # just the ip
			iphost = argv[1]
		elif l == 3: # ip and port
			iphost = argv[1]
			port = argv[2]
		elif l > 3:
			sys.exit("Too many arguments")

		self.pipeA, self.pipeB = Pipe()
		self.default_msg = "Dou I wanna ya ass'"
		self.nit_r = nit_recv(port)
		if iphost == "" or iphost == 'n':
			print "No valid send-to address, not sending"
		else:
			self.nit_s = nit_send(ip, port, self.pipeB)
			
		self.nit_r.start()
		if iphost == "" or iphost == 'n':
			self.nit_s.start()

		
		######################################################################
		### from here we check if it's a daemon styled server or a desktop ###
		######################################################################
		if sys.platform != "freebsd8": ### my server I was using
			self.root = Tk() ## so here we are a desktop, note the "!=" in the previous line
			frame = Frame(root)
			frame.pack()
			button = Button(frame, text="QUIT", fg="red", command=frame.quit)
			button.pack(side=LEFT)

			hi_there = Button(frame, text="Hello", command=self.sendmsg)
			hi_there.pack(side=LEFT)

	def sendmsg(self):
		self.pipeA.send(self.default_msg)
	def go(self):
		if sys.platform != "freebsd8":
			self.root.mainloop()
		else:
			while True:
				self.pipeA.send(raw_input("Type a message to send: > "))

##############################################################

n = nit(sys.argv)
n.go()
