## 1.装好cmake后建好文件夹，按照该文件夹的CMakeLists.txt内容进行编写
<br>

## 2.crtl+shift+p 输入 CMake configure，选择，后选择gcc编译器编译，选择后屏幕开始跳，生成build文件夹下的内容 也可直接点侧栏扩展下的cmake图标 选配置所有项目
<br>

## 3.输入 "mingw32-make.exe" 会在指定下生成 编译后的exe文件  或者cd bulid 进入build文件夹 cmake .. 然后再"mingw32-make.exe"
<br>

## 4.修改lanuch.json文件，让其调试文件名相同，返回main.cpp打断点调试
<br>

## CSDN博客：VSCode对多文件C++程序的多文件编译和调试

## 装cmake：官网下载，插入到环境变量 C:\Program Files\CMake\bin vscode安装CMake与CMake tool两个插件 写CMakeLists.txt