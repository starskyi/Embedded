from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow
import sys
from ui.Ui_my_main_window import Ui_MyMainWindow
from qt_material import apply_stylesheet

class MyMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.ui = Ui_MyMainWindow()
        self.ui.setupUi(self)

        self.init_ui()

    def on_button1_click(self):
        self.statusBar().showMessage(f"按钮按下了，当前值为：{self.ui.spinBox.value()}")

    def on_fresh_click(self):
        print("fresh!")

    def init_ui(self):
        self.ui.pushButton.clicked.connect(self.on_button1_click)
        self.ui.actionfresh.triggered.connect(self.on_fresh_click)

    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    apply_stylesheet(app, "dark_amber.xml")
    w = MyMainWindow()
    w.show()
    
    sys.exit(app.exec_())