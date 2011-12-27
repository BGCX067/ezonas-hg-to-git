import socket
import sys

UDP_IP="127.0.0.1"
if len(sys.argv) == 1:
	UDP_PORT = 5005
else:
	UDP_PORT = int(sys.argv[1])
	
sock = socket.socket( socket.AF_INET, # Internet
                      socket.SOCK_DGRAM ) # UDP
sock.bind( (UDP_IP,UDP_PORT) )

while True:
    data, addr = sock.recvfrom( 1024 ) # buffer size is 1024 bytes
    print sock.getsockname()
    print "received message:", data,"from", addr