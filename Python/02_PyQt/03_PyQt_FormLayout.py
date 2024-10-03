from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QVBoxLayout, QTextEdit, QPushButton, QFormLayout
from PyQt5.QtGui import QIcon, QPixmap
import sys

def button1_click():
    print("button1 clicked")

def init_widgets(w: QWidget):
    #设置布局
    layout = QFormLayout(w)
    # w.setLayout(layout)

    username = QLineEdit()
    username.setPlaceholderText("请输入用户名")

    password = QLineEdit()
    password.setPlaceholderText("请输入密码")
    password.setEchoMode(QLineEdit.Password)

    login_btn = QPushButton("登录")
    login_btn.clicked.connect(lambda: print("登录成功"))

    layout.addRow("username:", username)
    layout.addRow("password:", password)
    layout.addRow(login_btn)


if __name__ == "__main__":
    # 1.创建应用程序
    app = QApplication(sys.argv)

    # 2.创建窗口
    w = QWidget()

    # 设置标题，图标
    w.setWindowTitle("qtStart")
    w.setWindowIcon(QIcon("picture/icon1.jpg"))

    # w.resize(400, 300)

    # 设置窗口位置与大小
    #w.setGeometry(300, 200, 800, 600)


    # ----------------------------------------- 组件开始

    init_widgets(w)

    # ----------------------------------------- 组件结束


    # 3.显示窗口
    w.show()

    # 4.等待窗口停止
    sys.exit(app.exec())