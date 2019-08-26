MsgIPC是通过Hook的方式截取QQ消息并通过zeromq发布的一款dll插件，项目相关代码仅供学习参考。

## 说明

QQ版本：8.2(17724)

python目录下nogui.py为非pyside2即可运行。

## 截图
![screenshot](https://raw.githubusercontent.com/bstaint/MsgIPC/master/doc/screenshot.png)

## C++ dll

#### requires

 - minhook
 - cppzmq
 - msgpack
 - spdlog

## Python Client

#### requires

 - PySide2
 - pyzmq
 - msgpack