import sys
import commands
from PyQt4 import QtCore, QtGui, uic

# Cargar nuestro archivo .ui
form_class = uic.loadUiType("interfazInfo.ui")[0]
ruta=""
class MyWindowClass(QtGui.QMainWindow, form_class):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        com=['head -n 1 /proc/meminfo | cut -c18-24','uname -m',
        'cat /etc/issue.net','lscpu | grep -i \'model name\' | cut -c 24-63','nproc --all',
        'df -h /dev/sda1 | tail -n 1 | cut -c 18-20']

        self.ram.setText(str(int(self.comando(com[0]))/1024)+ " Mb")
        self.arq.setText(self.comando(com[1]))
        self.so.setText(self.comando(com[2]))
        self.proc.setText(self.comando(com[3]))
        self.nproc.setText(self.comando(com[4]))
        self.strg.setText(self.comando(com[5])+" Gb")
        self.seleccionar_ruta.clicked.connect(self.seleccionar_ruta_clicked)
        self.crear.clicked.connect(self.crear_clicked)
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

app = QtGui.QApplication(sys.argv)
MyWindow = MyWindowClass(None)
MyWindow.show()
app.exec_()
