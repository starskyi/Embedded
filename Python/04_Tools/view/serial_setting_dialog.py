
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from ui.Ui_SerialSetingDialog import Ui_SerialSettingDialog
import sys

class SerialSettingDialog(QDialog):

    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_SerialSettingDialog()
        self.ui.setupUi(self)

        # 可以通过此设置，固定对话框的大小
        self.setFixedSize(self.width(), self.height())
        self.initUi()

        self.baudrate = None

    def initUi(self):
        self.dataBits = 8
        self.stopBits = 1
        self.verifyBits = None
        self.flowControl = None

    def accept(self):
        super().accept()
        print("accept")
        # 读取当前波特率的设置值
        self.dataBits = self.ui.cb_data_bits.currentText()
        self.stopBits = self.ui.cb_stop_bits.currentText()
        self.verifyBits = self.ui.cb_verify_bits.currentText()
        self.flowControl = self.ui.cb_flow_control.currentText()

    def reject(self):
        super().reject()
        print("reject")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    dialog = SerialSettingDialog()
    dialog.show()
    sys.exit(app.exec_())