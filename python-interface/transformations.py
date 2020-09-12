# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'transformations.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPen, QBrush
from PyQt5.QtCore import Qt
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
        self.translationButton = QtWidgets.QPushButton(self.centralwidget)
        self.translationButton.setGeometry(QtCore.QRect(580, 10, 113, 32))
        self.translationButton.setObjectName("translationButton")
        self.rotationButton = QtWidgets.QPushButton(self.centralwidget)
        self.rotationButton.setGeometry(QtCore.QRect(580, 80, 113, 32))
        self.rotationButton.setObjectName("rotationButton")
        self.calibrationButton = QtWidgets.QPushButton(self.centralwidget)
        self.calibrationButton.setGeometry(QtCore.QRect(580, 150, 113, 32))
        self.calibrationButton.setObjectName("calibrationButton")
        self.generationButton = QtWidgets.QPushButton(self.centralwidget)
        self.generationButton.setGeometry(QtCore.QRect(580, 250, 113, 32))
        self.generationButton.setObjectName("generationButton")
        self.cancelButton = QtWidgets.QPushButton(self.centralwidget)
        self.cancelButton.setGeometry(QtCore.QRect(580, 420, 113, 32))
        self.cancelButton.setObjectName("cancelButton")
        self.lineEdit_Ty = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_Ty.setGeometry(QtCore.QRect(540, 20, 31, 21))
        self.lineEdit_Ty.setMaxLength(3)
        self.lineEdit_Ty.setObjectName("lineEdit_Ty")
        self.lineEdit_Tx = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_Tx.setGeometry(QtCore.QRect(480, 20, 31, 21))
        self.lineEdit_Tx.setMaxLength(3)
        self.lineEdit_Tx.setObjectName("lineEdit_Tx")
        self.lineEdit_rot = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_rot.setGeometry(QtCore.QRect(540, 90, 31, 21))
        self.lineEdit_rot.setObjectName("lineEdit_rot")
        self.lineEdit_Sy = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_Sy.setGeometry(QtCore.QRect(540, 160, 31, 21))
        self.lineEdit_Sy.setMaxLength(3)
        self.lineEdit_Sy.setObjectName("lineEdit_Sy")
        self.lineEdit_Sx = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_Sx.setGeometry(QtCore.QRect(480, 160, 31, 21))
        self.lineEdit_Sx.setMaxLength(3)
        self.lineEdit_Sx.setObjectName("lineEdit_Sx")
        self.lineEdit_gen = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_gen.setGeometry(QtCore.QRect(540, 260, 31, 21))
        self.lineEdit_gen.setMaxLength(3)
        self.lineEdit_gen.setObjectName("lineEdit_gen")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 700, 22))
        self.menubar.setObjectName("menubar")
        
        
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        
        self.x_cord = 150
        self.y_cord = 150
        self.pen  = QPen(Qt.blue)
        self.pen2 = QPen(Qt.red)
        
        self.translationButton.clicked.connect(lambda:self.translationFun())
        self.rotationButton.clicked.connect(lambda:self.rotationFun())
        self.calibrationButton.clicked.connect(lambda:self.calibrationFun())
        self.generationButton.clicked.connect(lambda:self.generationFun())
        self.cancelButton.clicked.connect(lambda:self.closeFun())

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Transformations"))
        self.translationButton.setText(_translate("MainWindow", "Translation"))
        self.rotationButton.setText(_translate("MainWindow", "Rotation"))
        self.calibrationButton.setText(_translate("MainWindow", "Calibration"))
        self.generationButton.setText(_translate("MainWindow", "Generate"))
        self.cancelButton.setText(_translate("MainWindow", "Cancel"))
        
        self.lineEdit_Ty.setText(_translate("MainWindow", "0"))
        self.lineEdit_Tx.setText(_translate("MainWindow", "0"))
        self.lineEdit_rot.setText(_translate("MainWindow", "45"))
        self.lineEdit_Sy.setText(_translate("MainWindow", "1"))
        self.lineEdit_Sx.setText(_translate("MainWindow", "1"))
        self.lineEdit_gen.setText(_translate("MainWindow", "100"))
        self.graphicsView.show()
        
        
    def closeFun(self):
        exit()
        
    
    def translationFun(self):
        self.scene.clear()
        
        Tx = float(self.lineEdit_Tx.text())
        Ty = float(self.lineEdit_Ty.text())
        side  = int(self.lineEdit_gen.text())
        matrix=[[1.0, 0., Tx],
                [0., 1.0, Ty],
                [0.,  0., 1.0]]
        points=[[self.x_cord,self.y_cord, 1],           [self.x_cord+side,self.y_cord, 1],
                [self.x_cord+side,self.y_cord+side, 1], [self.x_cord,self.y_cord+side, 1]]
        
        
        if side > 0 and side < 300:
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen)
            
            points = multi(points, matrix)
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen2)
    
    
    def rotationFun(self):
        self.scene.clear()
        
        rot  = float(self.lineEdit_rot.text())
        side = int(self.lineEdit_gen.text())
        matrix=[[ math.cos(rot* (math.pi/180)), math.sin(rot* (math.pi/180)), 0],
                [-math.sin(rot* (math.pi/180)), math.cos(rot* (math.pi/180)), 0],
                [0.,  0., 1.0]]
        points=[[self.x_cord,self.y_cord, 1],           [self.x_cord+side,self.y_cord, 1],
                [self.x_cord+side,self.y_cord+side, 1], [self.x_cord,self.y_cord+side, 1]]
        
        
        if side > 0 and side < 300:
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen)
            
            points = multi(points, matrix)
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen2)
    
    
    def calibrationFun(self):
        self.scene.clear()
        Sx = float(self.lineEdit_Sx.text())
        Sy = float(self.lineEdit_Sy.text())
        side  = int(self.lineEdit_gen.text())
        matrix=[[Sx, 0., 0.],
                [0., Sy, 0.],
                [0., 0., 0.]]
        points=[[self.x_cord,self.y_cord, 1],           [self.x_cord+side,self.y_cord, 1],
                [self.x_cord+side,self.y_cord+side, 1], [self.x_cord,self.y_cord+side, 1]]
        
        
        if side > 0 and side < 300:
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen)
            
            points = multi(points, matrix)
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen2)
    
    
    def generationFun(self):
        self.scene.clear()
        side = int(self.lineEdit_gen.text())
        
        points=[[self.x_cord,self.y_cord],           [self.x_cord+side,self.y_cord],
                [self.x_cord+side,self.y_cord+side], [self.x_cord,self.y_cord+side]]
        
        
        if side > 0 and side < 300:
            
            for i in range(-1, len(points)-1):
                self.scene.addLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1],self.pen)



def multiplyMatrixVector(vec, matrix):
    size   = len(vec)
    result = [0.]*size
    
    for i in range(size):
        for j in range(size):
            
            result[i] += matrix[i][j] * vec[j]
    
    return result


def multi(points, matrix):
    size = len(points)
    vec  = [0.]*len(matrix[0])
    
    for i in range(size):
        vec[0] = points[i][0]
        vec[1] = points[i][1]
        vec[2] = points[i][2]
        
        vec = multiplyMatrixVector(vec, matrix)
        
        points[i][0] = vec[0]
        points[i][1] = vec[1]
        points[i][2] = vec[2]
        
    return points




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
