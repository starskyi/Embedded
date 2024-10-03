from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QVBoxLayout, QTextEdit, QPushButton
from PyQt5.QtGui import QIcon, QPixmap
import sys

def button1_click():
    print("button1 clicked")

def init_widgets(w: QWidget):
    #设置布局
    layout = QVBoxLayout()

    # ----------------文本控件------------
    text_label = QLabel()
    text_label.setText("hello world")
    # text_label.setParent(w)
    layout.addWidget(text_label)
    
    # ----------------图片控件------------
    picture_label = QLabel()
    pixmap = QPixmap("picture/9.jpg")
    pixmap = pixmap.scaled(200, 200)
    picture_label.setPixmap(pixmap)
    # picture_label.setParent(w)
    # picture_label.setFixedSize(200, 200)
    layout.addWidget(picture_label)

    #----------------输入框---------------
    username = QLineEdit()
    username.setPlaceholderText("请输入用户名")
    # username.setParent(w)
    layout.addWidget(username)

    password = QLineEdit()
    password.setPlaceholderText("请输入密码")
    password.setEchoMode(QLineEdit.Password)
    # password.setParent(w)
    layout.addWidget(password)

    # ---------------多行输入---------------
    text_edit = QTextEdit()
    text_edit.setPlaceholderText("请输入描述")
    text_edit.setPlainText("你真漂亮")
    layout.addWidget(text_edit)

    # ---------------按钮-------------------
    button1 = QPushButton("button1")
    button1.clicked.connect(button1_click)
    layout.addWidget(button1)

    w.setLayout(layout)


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