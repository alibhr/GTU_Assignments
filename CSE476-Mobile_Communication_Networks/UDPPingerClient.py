from socket import *
from time import time
from time import strftime

client_socket = socket(AF_INET, SOCK_DGRAM)
client_socket.settimeout(1)

for i in range(1, 11):

	try:

		start_time = time()

		msg = f"Ping {i} {strftime('%H:%M:%S')}"
		client_socket.sendto(msg.encode(), ("", 12000))
		print(f"Sent Message: {msg}")

		data, server = client_socket.recvfrom(1024)
		print(f"Response Message: {data.decode()}", )

		end_time = time()

		print(f"RTT: {end_time - start_time}\n")

	except timeout:
		print(f"Request {i} Time Out\n")

print("\nShutting Down...\n")
client_socket.close()
