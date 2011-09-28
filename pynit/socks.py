import socket

ip_port = (socket.gethostname(), 10000)
print ip_port

# we create the socket and bind it
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# tells the socket to be reusable
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(ip_port)

sock.close()