import sys
import socket
print sys.argv

hostname = socket.gethostname()
print hostname[-5:]


print socket.gethostbyname(socket.gethostname())
print socket.gethostbyname(socket.getfqdn())
