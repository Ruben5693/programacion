import sys
import commands
from PyQt4 import QtCore, QtGui, uic
import libvirt

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

    def comando(self,com):
        res=commands.getstatusoutput(com)
        ram=0
        if res[0] == 0:
            ram=res[1]
        return ram


app = QtGui.QApplication(sys.argv)
MyWindow = MyWindowClass(None)
MyWindow.show()
app.exec_()
