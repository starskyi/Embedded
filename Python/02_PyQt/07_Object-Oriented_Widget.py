from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget
import sys
from ui.Ui_my_widget import Ui_Form

class MyWidget(QWidget):
    def __init__(self):
        super().__init__()
        
        self.ui = Ui_Form()
        self.ui.setupUi(self)

        self.init_ui()

    def on_button1_clicke(self):
        print("btn1 clicked")

    def init_ui(self):
        pass
        self.ui.button1.clicked.connect(self.on_btn1_clicked)

    

if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = MyWidget()
    w.show()
    
    sys.exit(app.exec_())