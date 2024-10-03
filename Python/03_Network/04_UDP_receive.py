import socket

receive_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

receive_socket.bind(("", 8888))
print("-------------开始接收--------------")
while True:
    msg, addr = receive_socket.recvfrom(1024)
    msg = msg.decode("UTF-8")
    print(f"{addr}: {msg}")