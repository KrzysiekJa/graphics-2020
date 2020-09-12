# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'transformations.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPen, QBrush
from PyQt5.QtCore import Qt, QPoint
import math



class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(700, 510)
        
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.scene = QtWidgets.QGraphicsScene() #!#
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setGeometry(QtCore.QRect(10, 10, 450, 450))
        self.graphicsView.setObjectName("graphicsView")
        
        self.firstButton = QtWidgets.QPushButton(self.centralwidget)
        self.firstButton.setGeometry(QtCore.QRect(580, 10, 113, 32))
        self.firstButton.setObjectName("firstButton")
        self.secondButton = QtWidgets.QPushButton(self.centralwidget)
        self.secondButton.setGeometry(QtCore.QRect(580, 80, 113, 32))
        self.secondButton.setObjectName("secondButton")
        self.thirdButton = QtWidgets.QPushButton(self.centralwidget)
        self.thirdButton.setGeometry(QtCore.QRect(580, 150, 113, 32))
        self.thirdButton.setObjectName("thirdButton")
        self.fourthButton = QtWidgets.QPushButton(self.centralwidget)
        self.fourthButton.setGeometry(QtCore.QRect(580, 250, 113, 32))
        self.fourthButton.setObjectName("fourthButton")
        self.fifthButton = QtWidgets.QPushButton(self.centralwidget)
        self.fifthButton.setGeometry(QtCore.QRect(580, 350, 113, 32))
        self.fifthButton.setObjectName("fifthButton")
        
        self.lineEdit_R = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_R.setGeometry(QtCore.QRect(540, 20, 31, 21))
        self.lineEdit_R.setMaxLength(3)
        self.lineEdit_R.setObjectName("lineEdit_R")
        self.lineEdit_N = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_N.setGeometry(QtCore.QRect(540, 90, 31, 21))
        self.lineEdit_N.setObjectName("lineEdit_N")
        self.lineEdit_Z = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_Z.setGeometry(QtCore.QRect(540, 160, 31, 21))
        self.lineEdit_Z.setMaxLength(3)
        self.lineEdit_Z.setObjectName("lineEdit_Z")
        self.lineEdit_value = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_value.setGeometry(QtCore.QRect(540, 360, 31, 21)) ###
        self.lineEdit_value.setMaxLength(3)
        self.lineEdit_value.setObjectName("lineEdit_value")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 700, 22))
        self.menubar.setObjectName("menubar")
        
        
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        
        
        self.pen = QPen(Qt.green)
        
        self.firstButton.clicked.connect(lambda:self.firstFun())
        self.secondButton.clicked.connect(lambda:self.secondFun())
        self.thirdButton.clicked.connect(lambda:self.thirdFun())
        self.fourthButton.clicked.connect(lambda:self.fourthFun())
        self.fifthButton.clicked.connect(lambda:self.fifthFun())

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Algorithms"))
        self.firstButton.setText(_translate("MainWindow", "First"))
        self.secondButton.setText(_translate("MainWindow", "Second"))
        self.thirdButton.setText(_translate("MainWindow", "Third"))
        self.fourthButton.setText(_translate("MainWindow", "Fourth"))
        self.fifthButton.setText(_translate("MainWindow", "Fifth"))
        
        self.lineEdit_R.setText(_translate("MainWindow", "100"))
        self.lineEdit_N.setText(_translate("MainWindow", "10"))
        self.lineEdit_Z.setText(_translate("MainWindow", "10"))
        self.lineEdit_value.setText(_translate("MainWindow", "15"))
        self.graphicsView.show()
    
    
    
    def firstFun(self):
        self.scene.clear()
        
        R = float(self.lineEdit_R.text())
        N = int(self.lineEdit_N.text())
        alfa  = 0.
        delta = 2. * math.pi/ N
        x, y, x0, y0 = 0, 0, 0, 0
        width, height = self.scene.width()/ 2., self.scene.height()/ 2.
        
        
        for i in range(N+1):
            x0 = x
            y0 = y
            x = int(R * math.cos(alfa) + width)
            y = int(R * math.sin(alfa) + height)
            alfa += delta
            
            if(i > 0):
                self.scene.addLine(x, y, x0, y0,self.pen)
        
    
    def secondFun(self):
        self.scene.clear()
        
        R = float(self.lineEdit_R.text())
        N = int(self.lineEdit_N.text())
        alfa  = 0.
        delta = 360./ N
        x, y, x0, y0 = 0, 0, 0, 0
        width, height = self.scene.width()/ 2., self.scene.height()/ 2.
        
        
        for i in range(N+1):
            x0 = x
            y0 = y
            x = int(R * math.cos(alfa) + width)
            y = int(R * math.sin(alfa) + height)
            alfa += delta
            
            if(i > 0):
                self.scene.addLine(x, y, x0, y0,self.pen)
        
    
    def thirdFun(self):
        self.scene.clear()
        
        R = float(self.lineEdit_R.text())
        N = int(self.lineEdit_N.text())
        Z = int(self.lineEdit_Z.text())
        alfa  = 0.
        delta = 2. * math.pi/ N
        dR    = R/ (N * Z)
        x, y, x0, y0, R = 0, 0, 0, 0, 0
        width, height = self.scene.width()/ 2., self.scene.height()/ 2.
        
        
        for i in range(N*Z):
            x0 = x
            y0 = y
            x = int(R * math.cos(alfa) + width)
            y = int(R * math.sin(alfa) + height)
            alfa += delta
            R += dR
            
            if(i > 0):
                self.scene.addLine(x, y, x0, y0,self.pen)
    
    
    def fourthFun(self):
        self.scene.clear()
        
        R = float(self.lineEdit_R.text())
        N = int(self.lineEdit_N.text())
        alfa  = 0.
        delta = 2. * math.pi/ N
        points = []
        x, y, = 0, 0
        width, height = self.scene.width()/ 2., self.scene.height()/ 2.
        
        
        for i in range(N+1):
            x = int(R * math.cos(alfa) + width)
            y = int(R * math.sin(alfa) + height)
            alfa += delta
            points.append((x,y))
            
        for i in range(N):
            for j in range(i,N):
                self.scene.addLine(points[i][0], points[i][1], points[j][0], points[j][1], self.pen)
    
    
    def fifthFun(self):
        self.scene.clear()
        
        value  = int(self.lineEdit_value.text())
        points = [[100, 100], [400, 100], [400, 400], [100, 400], [100, 100]]
        mi = 0.2
        x, y, = 0, 0
        
        
        for i in range(value):
            for j in range(4):
                points[j][0] = int((1-mi) * points[j][0] + mi * points[j+1][0])
                points[j][1] = int((1-mi) * points[j][1] + mi * points[j+1][1])    
            
            points[4] = points[0]
            
            for j in range(len(points)-1):
                self.scene.addLine(points[j][0], points[j][1], points[j+1][0], points[j+1][1], self.pen)




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
