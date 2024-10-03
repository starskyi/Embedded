from PyQt5 import QtCore
from PyQt5.QtGui import QCloseEvent
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow
import sys
from ui.Ui_MyMainWindow import Ui_MainWindow
from view.net_assistant_widget import NetAssisWidget
from view.serial_assistant_widget import SerialAssisWidget
from view.bluetooth_assistant_widget import BluetoothAssisWidget

from qt_material import apply_stylesheet

class MyMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.init_ui()


    def on_fresh_click(self):
        print("fresh!")

    # def closeEvent(self, event) -> None:
    #     event.accept()

    def init_ui(self):

        self.ui.tabWidget.addTab(NetAssisWidget(self), "网络助手")
        self.ui.tabWidget.addTab(SerialAssisWidget(self), "串口助手")
        self.ui.tabWidget.addTab(BluetoothAssisWidget(self), "蓝牙助手")
        

    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    # apply_stylesheet(app, "dark_amber.xml")
    w = MyMainWindow()
    w.show()
    sys.exit(app.exec_())