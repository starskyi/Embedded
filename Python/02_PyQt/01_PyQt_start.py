from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QIcon
import sys

# 1.创建应用程序
app = QApplication(sys.argv)

# 2.创建窗口
w = QWidget()

# 设置标题，图标
w.setWindowTitle("qtStart")
w.setWindowIcon(QIcon("picture/icon1.jpg"))

# w.resize(400, 300)

# 设置窗口位置与大小
w.setGeometry(300, 200, 800, 600)

w.setToolTip("这是一个窗口提示")

# 3.显示窗口
w.show()

# 4.等待窗口停止
sys.exit(app.exec())
