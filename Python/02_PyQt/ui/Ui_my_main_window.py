# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\code\embedded\Pthon\02_PyQt\ui\my_main_window.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MyMainWindow(object):
    def setupUi(self, MyMainWindow):
        MyMainWindow.setObjectName("MyMainWindow")
        MyMainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MyMainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalSlider = QtWidgets.QSlider(self.centralwidget)
        self.horizontalSlider.setGeometry(QtCore.QRect(100, 160, 160, 22))
        self.horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSlider.setObjectName("horizontalSlider")
        self.spinBox = QtWidgets.QSpinBox(self.centralwidget)
        self.spinBox.setGeometry(QtCore.QRect(130, 100, 46, 22))
        self.spinBox.setObjectName("spinBox")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(20, 100, 93, 28))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(200, 100, 93, 28))
        self.pushButton_2.setObjectName("pushButton_2")
        MyMainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MyMainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 26))
        self.menubar.setObjectName("menubar")
        self.menufile = QtWidgets.QMenu(self.menubar)
        self.menufile.setObjectName("menufile")
        self.menuedit = QtWidgets.QMenu(self.menubar)
        self.menuedit.setObjectName("menuedit")
        self.menutool = QtWidgets.QMenu(self.menubar)
        self.menutool.setObjectName("menutool")
        MyMainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MyMainWindow)
        self.statusbar.setObjectName("statusbar")
        MyMainWindow.setStatusBar(self.statusbar)
        self.actionnew_file = QtWidgets.QAction(MyMainWindow)
        self.actionnew_file.setObjectName("actionnew_file")
        self.actionopen_file = QtWidgets.QAction(MyMainWindow)
        self.actionopen_file.setObjectName("actionopen_file")
        self.actionsave_file = QtWidgets.QAction(MyMainWindow)
        self.actionsave_file.setObjectName("actionsave_file")
        self.actioncopy = QtWidgets.QAction(MyMainWindow)
        self.actioncopy.setObjectName("actioncopy")
        self.actionpast = QtWidgets.QAction(MyMainWindow)
        self.actionpast.setObjectName("actionpast")
        self.actionfresh = QtWidgets.QAction(MyMainWindow)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icon/res/refresh.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionfresh.setIcon(icon)
        self.actionfresh.setObjectName("actionfresh")
        self.menufile.addAction(self.actionnew_file)
        self.menufile.addAction(self.actionopen_file)
        self.menufile.addAction(self.actionsave_file)
        self.menuedit.addAction(self.actioncopy)
        self.menuedit.addAction(self.actionpast)
        self.menutool.addAction(self.actionfresh)
        self.menubar.addAction(self.menufile.menuAction())
        self.menubar.addAction(self.menuedit.menuAction())
        self.menubar.addAction(self.menutool.menuAction())

        self.retranslateUi(MyMainWindow)
        self.pushButton.clicked.connect(self.spinBox.stepDown) # type: ignore
        self.pushButton_2.clicked.connect(self.spinBox.stepUp) # type: ignore
        self.spinBox.valueChanged['int'].connect(self.horizontalSlider.setValue) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(MyMainWindow)

    def retranslateUi(self, MyMainWindow):
        _translate = QtCore.QCoreApplication.translate
        MyMainWindow.setWindowTitle(_translate("MyMainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MyMainWindow", "-"))
        self.pushButton_2.setText(_translate("MyMainWindow", "+"))
        self.menufile.setTitle(_translate("MyMainWindow", "file"))
        self.menuedit.setTitle(_translate("MyMainWindow", "edit"))
        self.menutool.setTitle(_translate("MyMainWindow", "tool"))
        self.actionnew_file.setText(_translate("MyMainWindow", "new file"))
        self.actionopen_file.setText(_translate("MyMainWindow", "open file"))
        self.actionsave_file.setText(_translate("MyMainWindow", "save file"))
        self.actioncopy.setText(_translate("MyMainWindow", "copy"))
        self.actionpast.setText(_translate("MyMainWindow", "past"))
        self.actionfresh.setText(_translate("MyMainWindow", "fresh"))
        self.actionfresh.setShortcut(_translate("MyMainWindow", "Alt+Shift+D"))
from ui import resource_rc
