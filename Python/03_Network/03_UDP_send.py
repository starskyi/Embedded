import socket

send_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    msg = input(">>").encode("UTF-8")
    send_socket.sendto(msg, ("127.0.0.1", 8888))
