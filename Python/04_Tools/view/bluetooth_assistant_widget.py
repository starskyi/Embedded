from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow
from qt_material import apply_stylesheet
import time
import sys
import threading
import atexit

from driver.driver_bluetooth import BluetoothDataTransfer
from ui.Ui_BluetoothAssisWidget import Ui_BluetoothAssisWidget

class BluetoothAssisWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.parent = parent
        self.bluetoothDevice: BluetoothDataTransfer = None

        self.ui = Ui_BluetoothAssisWidget()
        self.ui.setupUi(self)

        self.init_ui()

    def fresh_Thread(self):
        threading.Thread(target=self.fresh_device, daemon=True).start()

    def fresh_device(self):
        
        # 扫描所有蓝牙设备
        self.devices = BluetoothDataTransfer.scan_devices()

        self.ui.cb_devices.clear()

        # 找不到设备，直接返回
        if len(self.devices) <= 0:
            return
        
        for addr, name in self.devices:
            self.ui.cb_devices.addItem(name)

    def on_connect_click(self):
        # 已连接设备，此次断开
        if self.bluetoothDevice != None:

            self.close_connect()
            return

        device_index = self.ui.cb_devices.currentIndex()
        if device_index == -1:
            self.ui.recv_textEdit.append("请选择设备")
            return
        
        addr = self.devices[device_index][0]
        name = self.devices[device_index][1]

        # 连接
        
        self.bluetoothDevice = BluetoothDataTransfer(addr, name, 1)
        result = False
        try:
            result = self.bluetoothDevice.connect()
        except Exception as e:
            print(e)

        if result:
             # 连接成功
            self.ui.recv_textEdit.append("连接成功")
            # recv_thread = threading.Thread(target=self.recvMsg_Thread, daemon=True)
            # recv_thread.start()
        else:
            # 连接失败
            self.ui.recv_textEdit.append("连接失败")
            self.bluetoothDevice = None
                
        self.updataUI()   


    def close_connect(self):
        if self.bluetoothDevice == None:
            return

        self.bluetoothDevice.disconnect()

        self.bluetoothDevice = None
        self.updataUI()

    # 接受消息线程函数
    def recvMsg_Thread(self):
        while True:
            try:
                msg_byte = self.bluetoothDevice.receive_data()
                
                if len(msg_byte) == 0:
                    raise Exception("连接断开")

                encode = self.ui.cb_encode.currentText()
                msg_text = msg_byte.decode(encode)
                self.ui.recv_textEdit.append(msg_text)
            except Exception as e:
                # 连接断开，退出线程，关闭串口
                print(e)
                self.ui.recv_textEdit.append("连接已断开")
                self.close_connect()
                return
            
    

    def on_send_click(self):
        if self.bluetoothDevice == None:
            self.ui.recv_textEdit.append("请先连接设备")
            return

        # 发送数据
        msg = self.ui.send_textEdit.toPlainText()
        encode = self.ui.cb_encode.currentText()
        self.bluetoothDevice.send_data(msg.encode(encode))
        self.ui.recv_textEdit.append(f"已发送:{msg}")

    # 更新UI        
    def updataUI(self):
        if self.bluetoothDevice != None:
            self.ui.btn_connect.setText("断开连接（已连接）")
        else:
            self.ui.btn_connect.setText("连接")


    def init_ui(self):
        # threading.Thread(target=self.timer_fresh, daemon=True).start()
        self.fresh_Thread()
        self.ui.btn_refresh.clicked.connect(self.fresh_Thread)
        self.ui.btn_connect.clicked.connect(self.on_connect_click)
        self.ui.btn_send.clicked.connect(self.on_send_click)
    
      
    


    