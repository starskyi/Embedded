from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QVBoxLayout, QHBoxLayout, QTextEdit, QPushButton, QFormLayout
from PyQt5.QtGui import QIcon, QPixmap
import sys

def button1_click():
    print("button1 clicked")

def init_widgets(w: QWidget):
    #设置布局
    root_layout = QHBoxLayout(w)
    # w.setLayout(layout)

    vlayout1 = QVBoxLayout()
    vlayout1.addWidget(QPushButton("1"))

    vlayout2 = QVBoxLayout()
    vlayout2.addWidget(QPushButton("1"))
    vlayout2.addWidget(QPushButton("2"))

    vlayout3 = QVBoxLayout()
    vlayout3.addWidget(QPushButton("1"))
    vlayout3.addWidget(QPushButton("2"))
    vlayout3.addWidget(QPushButton("3"))
    vlayout3.addWidget(QPushButton("4"))

    root_layout.addLayout(vlayout1)
    root_layout.addLayout(vlayout2)
    root_layout.addLayout(vlayout3)

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