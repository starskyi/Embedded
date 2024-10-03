import threading
import socket

clients = []

def sendToUsers(client_socket: socket.socket, msg):

    for client in clients:

        # 不发给自己
        if client != client_socket:
            client.send(f"{client_socket.getpeername()}:".encode("UTF-8") + msg)

def client_thread(client_socket: socket.socket, addr):
    sendToUsers(client_socket, f"{addr}: 已上线".encode("UTF-8"))
    print(f"{addr}: 已上线")

    while True:
        try:
            msg = client_socket.recv(1024)
        except Exception as e:
            break
        
        msg_text = msg.decode("UTF-8")

        if not msg:
            break
        print(f"{addr}: {msg_text}")

        # 将消息发给其他用户
        sendToUsers(client_socket, msg)

    print(f"{addr}: 断开连接")
    clients.remove(client_socket)
    sendToUsers(client_socket, f"{addr}: 断开连接".encode("UTF-8"))
    
    

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("", 8888))
server_socket.listen(128)

while True:
    client_socket, addr = server_socket.accept()
    clients.append(client_socket)
    threading.Thread(target=client_thread, args=(client_socket, addr)).start()