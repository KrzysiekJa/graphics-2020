# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'into_lab.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui  import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *



class LineAnimation(QObject):
    def __init__(self, parent=None):
        super(LineAnimation, self).__init__()
        self.m_line = QLineF()
        self.m_item = QGraphicsLineItem()
        self.m_item.setLine(self.m_line)
        self.m_item.setPen(
                QPen(
                QColor("salmon"),
                5,
                Qt.SolidLine,
                Qt.SquareCap,
                Qt.RoundJoin,
            )
        )

        self.m_animation = QPropertyAnimation(
            self,
            b"p2",
            parent=self,
            startValue=QPointF(0, 0),
            endValue=QPointF(200, 250),
            duration=5000,
        )
        self.m_animation.start()

    def p1(self):
        return self.m_line.p1()

    def setP1(self, p1):
        self.m_line.setP1(p1)
        self.m_item.setLine(self.m_line)

    def p2(self):
        return self.m_line.p2()

    def setP2(self, p2):
        self.m_line.setP2(p2)
        self.m_item.setLine(self.m_line)
        
    p1 = pyqtProperty(QPointF, fget=p1, fset=setP1)
    p2 = pyqtProperty(QPointF, fget=p2, fset=setP2)




class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(500, 400)
        self.scene = QtWidgets.QGraphicsScene()
                
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setGeometry(QtCore.QRect(10, 10, 321, 321))
        self.graphicsView.setObjectName("graphicsView")
        self.closeButton = QtWidgets.QPushButton(self.centralwidget)
        self.closeButton.setGeometry(QtCore.QRect(350, 300, 113, 32))
        self.closeButton.setObjectName("closeButton")
        self.horizontalSlider = QtWidgets.QSlider(self.centralwidget)
        self.horizontalSlider.setGeometry(QtCore.QRect(340, 250, 131, 21))
        self.horizontalSlider.setMinimum(0)
        self.horizontalSlider.setMaximum(100)
        self.horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSlider.setObjectName("horizontalSlider")
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(350, 10, 113, 202))
        self.widget.setObjectName("widget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.liniaButton = QtWidgets.QPushButton(self.widget)
        self.liniaButton.setObjectName("liniaButton")
        self.verticalLayout.addWidget(self.liniaButton)
        self.lukButton = QtWidgets.QPushButton(self.widget)
        self.lukButton.setObjectName("lukButton")
        self.verticalLayout.addWidget(self.lukButton)
        self.bezierButton = QtWidgets.QPushButton(self.widget)
        self.bezierButton.setObjectName("bezierButton")
        self.verticalLayout.addWidget(self.bezierButton)
        self.polygonButton = QtWidgets.QPushButton(self.widget)
        self.polygonButton.setObjectName("polygonButton")
        self.verticalLayout.addWidget(self.polygonButton)
        self.tortButton = QtWidgets.QPushButton(self.widget)
        self.tortButton.setObjectName("tortButton")
        self.verticalLayout.addWidget(self.tortButton)
        self.elipsaButton = QtWidgets.QPushButton(self.widget)
        self.elipsaButton.setObjectName("elipsaButton")
        self.verticalLayout.addWidget(self.elipsaButton)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 500, 22))
        self.menubar.setObjectName("menubar")
        self.menuSave = QtWidgets.QMenu(self.menubar)
        self.menuSave.setObjectName("menuSave")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionSave = QtWidgets.QAction(MainWindow)
        self.actionSave.setObjectName("actionSave")
        self.actionLoad = QtWidgets.QAction(MainWindow)
        self.actionLoad.setObjectName("actionLoad")
        self.menuSave.addAction(self.actionSave)
        self.menuSave.addAction(self.actionLoad)
        self.menubar.addAction(self.menuSave.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        
        self.closeButton.clicked.connect(lambda:self.closeFun())
        self.liniaButton.clicked.connect(lambda:self.liniaFun())
        self.lukButton.clicked.connect(lambda:self.lukFun())
        self.bezierButton.clicked.connect(lambda:True)
        self.polygonButton.clicked.connect(lambda:self.polygonFun())
        self.tortButton.clicked.connect(lambda:self.tortFun())
        self.elipsaButton.clicked.connect(lambda:self.ellipseFun())

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Grafika"))
        self.closeButton.setText(_translate("MainWindow", "Close"))
        self.liniaButton.setText(_translate("MainWindow", "Linia"))
        self.lukButton.setText(_translate("MainWindow", "Łuk"))
        self.bezierButton.setText(_translate("MainWindow", "Bezier"))
        self.polygonButton.setText(_translate("MainWindow", "Polygon"))
        self.tortButton.setText(_translate("MainWindow", "Tort"))
        self.elipsaButton.setText(_translate("MainWindow", "Elipsa"))
        self.menuSave.setTitle(_translate("MainWindow", "File"))
        self.actionSave.setText(_translate("MainWindow", "Save"))
        self.actionLoad.setText(_translate("MainWindow", "Load"))
        self.graphicsView.show()
        
    def closeFun(self):
        exit()
        
    def liniaFun(self):
        self.scene.clear()
        
        self.scene.addLine(50, 50, 100, 100, QPen(Qt.red))
        self.scene.addLine(100, 100, 200, 50, QPen(Qt.green))
        self.scene.addLine(200, 50, 300, 350, QPen(Qt.blue))
        
    def lukFun(self):
        self.scene.clear()
        
    def polygonFun(self):
        self.scene.clear()
        pen   = QPen(Qt.red)
        brush = QBrush(Qt.red, Qt.Dense1Pattern)
        
        rect = self.scene.addRect(150, 150, 100, 100, pen, brush)
        
    def tortFun(self):
        self.scene.clear()
        
        line = LineAnimation(self)
        self.scene.addItem(line.m_item)
        
    def ellipseFun(self):
        self.scene.clear()
        pen   = QPen(Qt.green)
        brush = QBrush(Qt.green, Qt.DiagCrossPattern)
        
        ellipse = self.scene.addEllipse(100, 100, 150, 150, pen, brush)



if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
