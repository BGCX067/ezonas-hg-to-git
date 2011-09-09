import socket
import sys

UDP_IP="127.0.0.1"
if len(sys.argv) == 1:
	UDP_PORT = 5005
else:
	UDP_PORT = int(sys.argv[1])

MESSAGE="Hello, World!"

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
print sock.getsockname()
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))