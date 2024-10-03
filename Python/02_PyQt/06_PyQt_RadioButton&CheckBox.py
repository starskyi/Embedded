from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMessageBox, QRadioButton, QCheckBox, QButtonGroup, QVBoxLayout
from PyQt5.QtGui import QIcon
import sys



def login_btn_click():
    print(f"{btn1.isChecked()} {btn2.isChecked()} {checkBox1.isChecked()} {checkBox2.isChecked()} {checkBox3.isChecked()}")

def init_widgets(w: QWidget):
    global btn1
    global btn2
    global checkBox1
    global checkBox2
    global checkBox3

    vlayout = QVBoxLayout()

    # --------------------单选框---------------------
    w.setLayout(vlayout)

    btn_group = QButtonGroup()


    btn1 = QRadioButton("男")
    btn2 = QRadioButton("女")
    btn2.setChecked(True)
    
    btn_group.addButton(btn1)
    btn_group.addButton(btn2)
    

    vlayout.addWidget(btn1)
    vlayout.addWidget(btn2)

    # ---------------------复选框------------------------
    checkBox1 = QCheckBox("吃饭")
    checkBox2 = QCheckBox("睡觉")
    checkBox3 = QCheckBox("打游戏")
    checkBox3.setChecked(True)
    vlayout.addWidget(checkBox1)
    vlayout.addWidget(checkBox2)
    vlayout.addWidget(checkBox3)


    login_btn = QPushButton("登录")
    login_btn.clicked.connect(login_btn_click)
    vlayout.addWidget(login_btn)


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

   