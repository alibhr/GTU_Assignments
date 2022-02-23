from socket import *
import ssl
from base64 import b64encode

sourceAddr	= ""
password	= ""
destAddr	= ""

msg = "\r\n I love computer networks!"
subject = "Test Mail 0"
endmsg = "\r\n.\r\n"

# Choose a mail server (e.g. Google mail server) and call it mailserver
mailserver = ("smtp.gmail.com", 587)

# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect(mailserver)

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != "220":
	print("220 reply not received from server.")

# Send HELO command and print server response.
heloCommand = "HELO Alice\r\n".encode()
clientSocket.send(heloCommand)
recv1 = clientSocket.recv(1024).decode()
print(recv1)
if recv1[:3] != "250":
	print("250 reply not received from server.")

# This part is required for connect gmail smtp server because of security reasons.
clientSocket.send("STARTTLS\r\n".encode())
recv2 = clientSocket.recv(1024).decode()
print(recv2)
if recv2[:3] != "220":
	print("220 reply not received from server.")
clientSocket = ssl.wrap_socket(clientSocket)

# Authentication
clientSocket.send("AUTH LOGIN ".encode() + b64encode(sourceAddr.encode()) + "\r\n".encode())
recv3 = clientSocket.recv(1024).decode()
print(recv3)
if recv3[:3] != "334":
	print("334 reply not received from server.")

clientSocket.send(b64encode(password.encode()) + "\r\n".encode())
recv4 = clientSocket.recv(1024).decode()
print(recv4)
if recv4[:3] != "235":
	print("235 reply not received from server.")

# Send MAIL FROM command and print server response.
# This part carries the sender information.
clientSocket.send(f"MAIL FROM: <{sourceAddr}>\r\n".encode())
recv5 = clientSocket.recv(1024).decode()
print(recv5)
if recv5[:3] != "250":
	print("250 reply not received from server.")

# Send RCPT TO command and print server response.
# This part carries the receiver information.
clientSocket.send(f"RCPT TO: <{destAddr}>\r\n".encode())
recv6 = clientSocket.recv(1024).decode()
print(recv6)
if recv6[:3] != "250":
	print("250 reply not received from server.")

# Send DATA command and print server response. 
# Mail content information will come after the data command.
clientSocket.send("Data\r\n".encode())
recv7 = clientSocket.recv(1024).decode()
print(recv7)
if recv7[:3] != "354":
	print("354 reply not received from server.")

# Send message data.
# This part carries the content information of the mail.
# Message ends with a single period.
clientSocket.send(f"SUBJECT: {subject}\n{msg + endmsg}".encode())
recv8 = clientSocket.recv(1024).decode()
print(recv8)
if recv8[:3] != "250":
	print("250 reply not received from server.")

# Send QUIT command and get server response.
clientSocket.send("Quit\r\n".encode())
recv9 = clientSocket.recv(1024).decode()
print(recv9)
if recv9[:3] != "221":
	print('221 reply not received from server.')

clientSocket.close()
