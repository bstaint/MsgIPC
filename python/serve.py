import json
from PySide2.QtCore import QObject, Signal
from PySide2.QtWebSockets import QWebSocket, QWebSocketServer
from PySide2.QtNetwork import QHostAddress

class Serve(QObject):

    closed = Signal()
    recv = Signal(str)

    def __init__(self):
        super(Serve, self).__init__()
        self.client = None
        self.server = QWebSocketServer("Echo Server", QWebSocketServer.NonSecureMode)
        self.server.listen(QHostAddress.Any, 5678)
        self.server.newConnection.connect(self.onNewConnection)
        self.server.closed.connect(self.closed)

    def onNewConnection(self):
        if not self.client:
            self.client = self.server.nextPendingConnection()
            self.client.textMessageReceived.connect(self.recv)

    def proessTextMessage(self, message):
        self.recv.emit(message)

    def send(self, text):
        if self.client:
            self.client.sendTextMessage(text)
