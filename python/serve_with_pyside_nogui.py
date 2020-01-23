from serve import Serve
from PySide2.QtCore import QCoreApplication

if __name__ == '__main__':
    app = QCoreApplication(sys.argv)
    s = Serve()
    sys.exit(app.exec_())
