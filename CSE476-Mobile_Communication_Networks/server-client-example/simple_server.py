from socket import *


def create_server():

    server_socket = socket(AF_INET, SOCK_STREAM)

    try:
        server_socket.bind(('10.242.3.167', 8089))
        print("HERE")
        server_socket.listen(5)
        while True:

            (clientSocket, address) = server_socket.accept()

            rd = clientSocket.recv(5000).decode()
            pieces = rd.split("\n")
            if len(pieces) > 0:
                print(pieces[0])

            data = "HTTP/1.1 200 OK\r\n" \
                   "Content-Type: text/html; charset-utf-8\r\n" \
                   "\r\n" \
                   "<html><body>Hello my friend 1</body></html>\r\n\r\n"

            clientSocket.sendall(data.encode())
            clientSocket.shutdown(SHUT_WR)

    except KeyboardInterrupt:
        print("\nshutting down...\n")

    except Exception as exc:
        print("Error : ", end="")
        print(exc)

    server_socket.close()


create_server()
