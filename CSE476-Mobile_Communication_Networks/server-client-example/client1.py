from socket import *

my_socket = socket(AF_INET, SOCK_STREAM)

try:
    my_socket.connect(("data.pr4e.org", 80))
except Exception as exc:
    print("Error1: ",exc)
    exit()

cmd = "Get http://data.pr4e.org/romeo.txt HTTP/1.0\r\n\r\n".encode()
my_socket.send(cmd)

while True:
    data = my_socket.recv(512)
    if len(data) < 1 :
        break
    print(data.decode(),end='')

my_socket.close()
