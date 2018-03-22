from __future__ import print_function
import sys
import libvirt
import commands
from PyQt4 import QtCore, QtGui, uic

# Cargar nuestro archivo .ui
form_class = uic.loadUiType("interfazInfo.ui")[0]
ruta=""
class MyWindowClass(QtGui.QMainWindow, form_class):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.info()
        self.seleccionar_ruta.clicked.connect(self.seleccionar_ruta_clicked)

    # Ejecutar comando
    def comando(self,com):
        res=commands.getstatusoutput(com)
        ram=0
        if res[0] == 0:
            ram=res[1]
        return ram

    # Evento del boton seleccionar_ruta
    def seleccionar_ruta_clicked(self):
        text = QtGui.QFileDialog.getOpenFileName(self, 'Open file', '/home',"Imagen (*.iso)")
        self.ruta_set.setText(str(text))
    # Evento del boton crear
    def crear_clicked(self):
        com='sh plantilla.sh '
        self.comando(com[1])

    def info(self):
        conn = libvirt.open('qemu:///system')
        if conn == None:
            #print('Failed to open connection to qemu:///system', file=sys.stderr)
            exit(1)

        nodeinfo = conn.getInfo()

        self.arq.setText(str(nodeinfo[0]))
        self.ram.setText(str(nodeinfo[1])+' MB')
        self.nproc.setText(str(nodeinfo[2]))
        self.potencia.setText(str(nodeinfo[3])+' MHz')

        conn.close()



app = QtGui.QApplication(sys.argv)
MyWindow = MyWindowClass(None)
MyWindow.show()
app.exec_()
