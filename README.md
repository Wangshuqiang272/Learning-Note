# INTRODUCE
    本仓库主要用来记录笔者个人学习记录

# NOTE
## Cmake部分
### 1.Cmake学习记录中记录了Cmake的各种命令讲解以及各步骤的说明
### 2.使用时，进入到各个STEPX目录下，执行以下命令：
#### 1.mkdir build //存放编译缓存文件
#### 2.cmake --version //查询cmake版本，测试时用的cmake版本为3.23.1,使用时版本不得低于3.23.0，也可以修改CMakeLists.txt中的第一句话
#### 3.cmake -B ./build //运行cmake -B 用来缓存指定文件夹
#### 4.cd build //进入缓存文件夹
#### 5.make && ./Launcher   //运行makefile 执行可执行文件