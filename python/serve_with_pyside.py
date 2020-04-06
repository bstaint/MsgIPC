import sys
import json
from PySide2.QtWidgets import QApplication, QWidget, QMessageBox
from PySide2.QtCore import QFile
from ui_form import Ui_Form
from serve import Serve
from enum import Enum, unique

@unique
class Message(Enum):
    UNKNOWN = -1
    ERROR = 0
    OK = 1
    SELFUIN = 2
    CHAT = 3
    TEST = 4

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ui.pushButton.clicked.connect(self.pushButton1Clicked)
        self.ui.pushButton_2.clicked.connect(self.pushButton2Clicked)
        self.serve = Serve()
        self.serve.recv.connect(self.recvText)

    def pushButton1Clicked(self):
        self.serve.send(json.dumps({'errno': Message.PSELFUIN.value }))

    def pushButton2Clicked(self):
        self.serve.send(json.dumps({'errno': Message.PTEST.value }))
        # error message
        self.serve.send(json.dumps({'type': Message.PTEST.value }))

    def recvText(self, text):
        try:
            obj = json.loads(text)
        except json.decoder.JSONDecodeError:
            return

        errno = int(obj['errno'])
        if errno == Message.CHAT.value:
            self.ui.listWidget.addItem(
                'group:{group} {nickname}({sender}): {text}'.format(**obj['message'])
            )
        elif errno == Message.SELFUIN.value:
            QMessageBox.information(self, 'test', obj['message'])


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
