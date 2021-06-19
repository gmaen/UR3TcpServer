```
UR3TCPSEREVER
|-build
|-configs
|-dist
|-src
| |-config
| |-log
| |-server
|-CMakeLists.txt
|-readme.md
```

1. 编译(使用gnu make)
  1. 进入build文件夹
  2. windows:
     ```
     cmake -G "MinGW Makefiles" ..
     ```
     linux:
     ```
     cmake ..
     ```
  3. make

2. 配置
  1. client：robot： 机械臂IP地址
  2. client：usefixedcontrol： 控制器IP地址是否固定
  3. client：control： 控制器IP地址
  4. server：address： 服务器IP地址
  5. server：port： 服务器开放的端口