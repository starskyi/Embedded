import socket


tcp_socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # 连接远端
    tcp_socket_client.connect(("127.0.0.1", 8888))
except Exception as e:
    print(e)
    print("网络异常，请稍后再试")


while True:
    str = input(">>").encode("UTF-8")
    try:
        tcp_socket_client.send(str)
    except Exception as e:
        print(e)
        tcp_socket_client.close()
        break


