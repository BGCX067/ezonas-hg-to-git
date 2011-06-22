import socket

sock = socket.socket(socket.AF_INET, # Internet
                      socket.SOCK_DGRAM ) # UDP
#sock.bind((socket.gethostname(), 65000))

while True:
    data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    print "received message:", data, "from", addr