# import socket module
from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)

# Prepare a sever socket
port = 80
ip = ""

serverSocket.bind((ip,port))
print(f"Server socket binded to {ip}:{port}")

serverSocket.listen(1)

while True:

	try:
		# Establish the connection
		print("Ready to serve...")
		connectionSocket, addr = serverSocket.accept()
		print(f"connectionSocket: {connectionSocket}, addr: {addr}")

		message = connectionSocket.recv(1024).decode()

		s_msg = message.split()
		filename = ""
		if(len(s_msg) > 1):
			filename = s_msg[1]
		else:
			print("Empty file name")
			raise IOError
		
		f = open(filename[1:])
		outputdata = f.read()

		# Send one HTTP header line into socket
		connectionSocket.send(
			"HTTP/1.1 200 OK\r\n"								\
			"Content-Type: text/html; charset-utf-8\r\n\r\n"	\
			.encode()
		)

		# Send the content of the requested file to the client
		for i in range(0, len(outputdata)):
			connectionSocket.send(outputdata[i].encode())
		connectionSocket.close()

		f.close()

	except IOError:
		#Send response message for file not found
		response =	"HTTP/1.1 404 Not Found\r\n"					\
					"Content-Type: text/html; charset-utf-8\r\n"	\
					"\r\n" 											\
					"<html>" 										\
					"\t<head>"										\
					"\t<title>"										\
					"\t\t404 Not Found"								\
					"\t</title>"									\
					"\t</head>"										\
					"\t<body>"										\
					"\t\t<h1>"										\
					"\t\t\t404 Not Found "							\
					"\t\t</h1>"										\
					"\t</body>"										\
					"</html>".encode()

		connectionSocket.sendall(response)

		#Close client socket
		connectionSocket.close()

	except KeyboardInterrupt:
		print("\nShutting Down...\n")
		break

serverSocket.close()
