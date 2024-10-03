from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QVBoxLayout, QTextEdit, QPushButton, QMessageBox
from PyQt5.QtGui import QIcon, QPixmap
import sys

def button1_click():
    result = QMessageBox.question(w, "提示", "是否登录", QMessageBox.Yes | QMessageBox.Cancel, QMessageBox.Cancel)
    
    if result == QMessageBox.Yes:
        QMessageBox.information(w, "提示", "登录成功")
    elif result == QMessageBox.Cancel:
        QMessageBox.information(w, "提示", "登录失败")

def init_widgets(w: QWidget):
    
    button1 = QPushButton("button1")
    button1.clicked.connect(button1_click)
    button1.setParent(w)
    

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

   