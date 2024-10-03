from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow
import sys
import socket
import threading

from ui.Ui_NetAssistantWidget import Ui_NetAssistant
from qt_material import apply_stylesheet

class NetAssisWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.clients = []
        self.ui = Ui_NetAssistant()
        self.ui.setupUi(self)

        self.init_ui()
       
    # 接收新客户端，执行新线程
    def receive_client_thread(self, client_socket: socket.socket, addr):
        self.ui.msgTextEdit.append(f"({addr[0]}:{addr[1]}): 已上线")
        while True:
            try:
                msg = client_socket.recv(1024)
            except Exception as e:
                break

            try:
                msg_text = msg.decode(self.ui.encodeBox.currentText())
            except Exception as e:
                print(e)
                msg_text = msg.decode("GBK")

            if not msg:
                break
            self.ui.msgTextEdit.append(f"({addr[0]}:{addr[1]}): {msg_text}")

        self.ui.msgTextEdit.append(f"({addr[0]}:{addr[1]}): 断开连接")
        self.clients.remove(client_socket)

    # 循环接收来自服务端的信息
    def recv_tcp_msg(self):
        peer_ip = self.server_socket.getpeername()[0]
        peer_port = self.server_socket.getpeername()[1]
        while True:
            try:
                msg = self.server_socket.recv(1024)
        
                if not msg:
                    # 远程服务端已断开连接，退出
                    # 设置按钮当前状态
                    self.ui.connectBtn.setText("连接")
                    self.ui.msgTextEdit.append(f"({peer_ip}:{peer_port}):远程服务器已断开")
                    return

            except Exception as e:
                # client_socket已关闭，退出线程
                print(e)
                return
            
            try:
                msg_text = msg.decode(self.ui.encodeBox.currentText())
            except Exception as e:
                msg_text = msg.decode("GBK")
                print(e)
            
            self.ui.msgTextEdit.append(f"({peer_ip}:{peer_port}):{msg_text}")
        

    # 客户端连接服务端
    def run_tcp_client(self, target_ip, target_port):
        
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.server_socket.connect((target_ip, int(target_port)))
        except Exception as e:
            print(e)
            self.ui.msgTextEdit.append("连接失败!")
            self.server_socket.close()
            # 设置按钮当前状态
            self.ui.connectBtn.setText("连接")

            return
        self.ui.msgTextEdit.append("连接成功!")

        threading.Thread(target=self.recv_tcp_msg, daemon=True).start()

    # 开启服务端
    def run_tcp_server(self, target_ip, target_port):
        
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.server_socket.bind((target_ip, int(target_port)))
        except Exception as e:
            print(e)
            self.ui.msgTextEdit.append("连接失败!")
            # 设置按钮当前状态
            self.ui.connectBtn.setText("连接")
            return
        self.ui.msgTextEdit.append("连接成功!")

        self.server_socket.listen(128)   

        # 不停接收新客户
        while True:
            try:
                client_socket, addr = self.server_socket.accept()
            except Exception as e:
                # server_socket已关闭，关闭线程
                print(e)
                return
            
            self.clients.append(client_socket)
            threading.Thread(target=self.receive_client_thread, args=(client_socket, addr), daemon=True).start()


    # 连接按钮点击事件
    def on_connect_click(self):
        self.ui.connectBtn.setEnabled(False)
        target_ip = self.ui.target_ip.text() if self.ui.target_ip.text() != "..." else ""
        target_port = self.ui.target_port.text()
        connect_status = self.ui.connectBtn.text()
        
        # 按钮当前状态是否连接
        if connect_status == "连接":
             #设置按钮当前状态
            self.ui.connectBtn.setText("断开连接（已连接）")

            # 开始链接
            text = self.ui.setModeBox.currentText()
            if text == "TCP客户端":
                self.run_tcp_client(target_ip, target_port)
            elif text == "TCP服务端":
                self.server_thread = threading.Thread(target=self.run_tcp_server, args=(target_ip, target_port), daemon=True).start()
            elif text == "UDP":
                pass
        else:
           self.disconnect() 
            
        self.ui.connectBtn.setEnabled(True)

    
    def disconnect(self):
        #断开连接
        self.ui.msgTextEdit.append("断开连接")
        self.server_socket.close()
        
        #设置按钮当前状态
        self.ui.connectBtn.setText("连接")

    # 发送按钮点击事件
    def on_sendBtn_click(self):
        msg = self.ui.sendTextEdit.toPlainText()
        try:
            self.server_socket.sendall(msg.encode("UTF-8"))
            self.ui.recv_textEdit.append(f"已发送:{msg}")
        except Exception as e:
            print(e)

    def on_mode_change(self):
        try:
            # 没有实际作用，当server_socket断开连接时触发特定异常
            self.server_socket.getpeername()

            self.server_socket.close()
            self.ui.msgTextEdit.append("断开连接")
        except AttributeError as e:
            print(e)
        except OSError as e:
            print(e)


        #设置按钮当前状态
        self.ui.connectBtn.setText("连接")


    def init_ui(self):
        self.ui.target_ip.setText("127.0.0.1")
        self.ui.target_port.setText("8888")

        self.ui.connectBtn.clicked.connect(self.on_connect_click)
        self.ui.sendMsgBtn.clicked.connect(self.on_sendBtn_click)
        self.ui.setModeBox.currentIndexChanged.connect(self.on_mode_change)
        

    