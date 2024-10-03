import socket
import threading


def send_msg():
    while True:
        str = input(">>").encode("UTF-8")
        try:
            tcp_socket_client.send(str)
        except Exception as e:
            print(e)
            tcp_socket_client.close()
            break


def receive_msg():
    msg = tcp_socket_client.recv(1024)
    msg_text = msg.decode("UTF-8")
    print(msg_text)

tcp_socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # 连接远端
    tcp_socket_client.connect(("127.0.0.1", 8888))
except Exception as e:
    print(e)
    print("网络异常，请稍后再试")


threading.Thread(target=send_msg).start()
threading.Thread(target=receive_msg).start()



