import sys
from serve import Serve
from PySide2.QtCore import QCoreApplication

def recv(text):
    print(text)

if __name__ == '__main__':
    app = QCoreApplication(sys.argv)
    s = Serve()
    s.recv.connect(recv)
    sys.exit(app.exec_())
