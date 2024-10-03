from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow
from qt_material import apply_stylesheet
import time
import sys
import threading
import atexit

from ui.Ui_SerialAssisWidget import Ui_SerialAssisWidget
from driver.serial_driver import scan_serial_ports, SerialDevice
from view.serial_setting_dialog import SerialSettingDialog


class SerialAssisWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        
        self.serialDriver: SerialDevice = None

        self.ui = Ui_SerialAssisWidget()
        self.ui.setupUi(self)

        self.init_ui()

    def timer_fresh(self):
        while True:
            self.fresh_device()
            time.sleep(1)

    # 刷新设备列表
    def fresh_device(self):
        self.ui.cb_device.clear()
        self.devices = scan_serial_ports()

        # 找不到设备，直接返回
        if len(self.devices) <= 0:
            return
        
        for device, description in self.devices:
            self.ui.cb_device.addItem(description)


    # 更新UI
    def updataUI(self):
        if self.serialDriver:
            self.ui.btn_connect.setText("断开连接（已连接）")
        else:
            self.ui.btn_connect.setText("连接设备")

    # 接受消息线程函数
    def recvMsg_Thread(self):
        while True:
            try:
                msg_byte = self.serialDriver.readline()
                encode = self.ui.cb_encode.currentText()
                msg_text = msg_byte.decode(encode)
            except Exception as e:
                # 连接断开，退出线程，关闭串口
                print(e)
                self.ui.recv_textEdit.append("连接已断开")
                self.close_connect()
                return

            self.ui.recv_textEdit.append(msg_text)

    # 连接设备按钮事件
    def on_connect_click(self):
        # 已连接设备，此次断开
        if self.serialDriver != None:

            self.close_connect()
            return

        device_index = self.ui.cb_device.currentIndex()
        baud_value = self.ui.cb_baud_rate.currentText()

        # 未选择设备
        if device_index == -1:
            self.ui.recv_textEdit.append("请选择设备")
            return
        
        port = self.devices[device_index][0]

        self.serialDriver = SerialDevice(port, int(baud_value), 1)
        if self.serialDriver.open():
            # 连接成功
            self.ui.recv_textEdit.append("连接成功")
            recv_thread = threading.Thread(target=self.recvMsg_Thread, daemon=True)
            recv_thread.start()
        else:
            # 连接失败
            self.ui.recv_textEdit.append("连接失败")
            self.serialDriver = None

        self.updataUI()

    # 串口设置按钮事件
    def on_baudSet_click(self):
        dialog = SerialSettingDialog()
        # dialog.show()
        dialog.exec_()

    # 发送按钮点击事件
    def on_send_click(self):
        if self.serialDriver == None:
            self.ui.recv_textEdit.append("请先连接设备")
            return

        # 发送数据
        msg = self.ui.send_textEdit.toPlainText()
        encode = self.ui.cb_encode.currentText()
        self.serialDriver.write(msg.encode(encode))
        self.ui.recv_textEdit.append(f"已发送:{msg}")


    def close_connect(self):
        if self.serialDriver == None:
            return 

        if self.serialDriver.is_open():
            self.serialDriver.close()

        self.serialDriver = None
        self.updataUI()

    def init_ui(self):
        # threading.Thread(target=self.timer_fresh, daemon=True).start()
        self.fresh_device()
        self.ui.btn_refresh.clicked.connect(self.fresh_device)
        self.ui.btn_connect.clicked.connect(self.on_connect_click)
        self.ui.btn_baud_set.clicked.connect(self.on_baudSet_click)
        self.ui.btn_send.clicked.connect(self.on_send_click)
        self.ui.btn_clearRecv.clicked.connect(self.ui.recv_textEdit.clear)
      
    


    