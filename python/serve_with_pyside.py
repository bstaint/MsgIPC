import sys
import json
from PySide2.QtWidgets import QApplication, QWidget, QMessageBox
from PySide2.QtCore import QFile
from ui_form import Ui_Form
from serve import Serve

class MainWindow(QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.ui.pushButton.clicked.connect(self.pushButton1Clicked)
        self.ui.pushButton_2.clicked.connect(self.pushButton1Clicked)
        self.serve = Serve()
        self.serve.recv.connect(self.recvText)

    def pushButton1Clicked(self):
        data = {'type': 1, 'errno': 1}
        self.serve.send(json.dumps(data))

    def recvText(self, text):
        try:
            obj = json.loads(text)
        except json.decoder.JSONDecodeError:
            return

        if obj['errno'] == '0':
            msg = obj['message']
            if isinstance(msg, str):
                QMessageBox.information(self, 'test', msg)
            else:
                self.ui.listWidget.addItem(
                    f'group:{msg["group"]} {msg["nickname"]}({msg["sender"]}): {msg["text"]}'
                )


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
