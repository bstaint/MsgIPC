import sys
import zmq
import msgpack
from PySide2 import QtWidgets, QtCore
from ui_main import Ui_Form


class TaskSignal(QtCore.QObject):

    say = QtCore.Signal(str)

class Task(QtCore.QRunnable):

    def __init__(self):
        super(Task, self).__init__()
        self.signals = TaskSignal()

    def run(self):
        context = zmq.Context()
        sub = context.socket( zmq.SUB )
        sub.connect( "tcp://127.0.0.1:5555" )
        sub.setsockopt(zmq.LINGER, 0)
        sub.setsockopt_string(zmq.SUBSCRIBE, "")

        while True:
            bytes_ = sub.recv()
            uin, gin, nickname, text = msgpack.unpackb(bytes_, raw=False)
            self.signals.say.emit(f"group:{gin} {nickname}({uin}): {text}")

        sub.close()
        context.term()  

class MyApp(QtWidgets.QWidget):

    def __init__(self):
        super(MyApp, self).__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        
        task = Task()
        task.signals.say.connect(self.say)
        QtCore.QThreadPool.globalInstance().start(task)

    def say(self, text):
        self.ui.listWidget.addItem(text)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)

    w = MyApp()
    w.show()

    sys.exit(app.exec_())