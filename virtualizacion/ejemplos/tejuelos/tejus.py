#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
from PyQt4 import QtGui, uic
import commands
import codecs

class MyWindow(QtGui.QMainWindow):
    def __init__(self):
        #lpr -P tejuelos -o raw /tmp/tejuelos
        self.CABECERA_DE="BICC"
        self.CABECERA_IZ="UEX"
        self.IMPRESORA="tejuelos"
        super(MyWindow, self).__init__()
        uic.loadUi('/home/ruben/Escritorio/virtualizacion/ejemplos/tejuelos/mainwindow.ui', self)
        self.show()
        self.setWindowTitle(self.CABECERA_DE+" TEJUELOS")
        self.cabecera.setText(self.CABECERA_IZ+"                     "+self.CABECERA_DE)
        self.impresora.setText("Impresora:  "+self.IMPRESORA)
        self.imprimir.clicked.connect(self.imprime)
        self.reset.clicked.connect(self.borrar)
    def imprime(self):
        lines = self.signaturas.toPlainText().split("\n")
        outfile = codecs.open('/tmp/tejuelos', 'w','iso-8859-1')
        outfile.write('FR"TEJU"\n')

        for l in lines:
            l.replace("  "," ")

            part=l.split(" ")
            if len(l)!=0:
              print "--"+str(len(l))+" __ "+l+";"
              outfile.write('?\n')
              outfile.write(self.CABECERA_DE+"\n")
              for i in range(0,len(part)):
                  print str(i)+"  "+unicode(part[i])
                  outfile.write(unicode(part[i])+"\n")
              for i in range(len(part),3):
                  outfile.write(" \n")
                  print str(i)+"  "
              outfile.write('P1\n')
        outfile.close()
        cmd = "lpr -P "+self.IMPRESORA+" -o raw /tmp/tejuelos"
        print cmd
        commands.getoutput(cmd)
    def borrar(self):
        self.signaturas.clear();


if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    window = MyWindow()
    sys.exit(app.exec_())
