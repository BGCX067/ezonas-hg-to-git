import socket

UDP_PORT=65000
MESSAGE="Hello, World!"


print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, # Internet
				   socket.SOCK_DGRAM) # UDP
sock.sendto(MESSAGE, ('spark.ofloo.net', UDP_PORT))