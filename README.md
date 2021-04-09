MsgIPC是通过Hook的方式截取QQ消息并通过zeromq发布的一款dll插件，项目相关代码仅供学习参考。

## 说明

QQ版本：8.2(17724)

python目录下nogui.py为非pyside2即可运行。

### 注意：
新版QQ确保关闭QQProtect进程（QQ_SecurityCheck_Patch_v12.1(for_v9.2.x).exe），`KernelUtil.dll`中`CheckVideoMsg`导出符号是否一致。

## 截图
![screenshot](https://raw.githubusercontent.com/bstaint/MsgIPC/master/doc/screenshot.png)

## C++ dll

pro文件中引用第三方pri文件参考：
[https://github.com/bstaint/3rdparty](https://github.com/bstaint/3rdparty)

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
