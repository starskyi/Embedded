import socket

tcp_socket_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

tcp_socket_server.bind(("", 8888))
tcp_socket_server.listen(128)

while True:
    client_socket, addr = tcp_socket_server.accept()
    print(type(client_socket.getpeername()), f" {client_socket.getpeername()}")
    while True:
        msg = client_socket.recv(1024)
        if(len(msg) == 0):
            print(f"{addr} 已断开连接")
            break
        print(msg)