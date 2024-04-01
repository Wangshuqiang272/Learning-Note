

# Cmake学习记录

## STEP 1：编译一个由一个源文件生成的二进制文件

### 1.最简单的项目由一个源文件构成，CMakeList.txt文件只需要两行即可

```cmake
#标定该cmake运行所需的cmake最低版本，安装的cmake版本不得低于该版本
cmake_minimum_required
#指定当前工程名称
project(Launcher)
#使用指定源文件来生成目标可执行文件
add_executable(Launcher main.c)
```



**project**命令解析

1. 实际上在调用project命令指定当前工程名字的同时，cmake内部会为如下变量赋值：

   - PROJECT_NAME

   - PROJECT_SOURCE_DIR

   - PROJECT_BINARY_DIR

   - CMAKE_PROJECT_NAME

   - 实例如下：

     ```cmake
     message("wangshuqiang PROJECT_NAME -> ${PROJECT_NAME}")
     message("wangshuqiang PROJECT_SOURCE_DIR -> ${PROJECT_SOURCE_DIR}")
     message("wangshuqiang PROJECT_BINARY_DIR -> ${PROJECT_BINARY_DIR}")
     message("wangshuqiang CMAKE_PROJECT_NAME -> ${CMAKE_PROJECT_NAME}")
     #运行结果
     wangshuqiang PROJECT_NAME -> Launcher
     wangshuqiang PROJECT_SOURCE_DIR -> /mnt/d/Data/learningNote/Learning-Note/Cmake/src
     wangshuqiang PROJECT_BINARY_DIR -> /mnt/d/Data/learningNote/Learning-Note/Cmake/src/build
     wangshuqiang CMAKE_PROJECT_NAME -> Launcher
     ```

     ​

2. 选项 **VERSION**

   当使用project命令时，若带上了VERSION选项，则指定了工程的版本号，格式如下

   ​	 `project(Launcher VERSION X.X.X.X)`

   同样，当使用了VERSION选项，如下变量会相应被赋值

   - PROJECT_VERSION

   - PROJECT_VERSION_MAJOR

   - PROJECT_VERSION_MINOR

   - PROJECT_VERSION_PATCH

   - PROJECT_VERSION_TWEAK

   - CMAKE_PROJECT_VERSION

     ```cmake
     message("wangshuqiang PROJECT_VERSION -> ${PROJECT_VERSION}")
     message("wangshuqiang PROJECT_VERSION_MAJOR -> ${PROJECT_VERSION_MAJOR}")
     message("wangshuqiang PROJECT_VERSION_MINOR -> ${PROJECT_VERSION_MINOR}")
     message("wangshuqiang PROJECT_VERSION_PATCH -> ${PROJECT_VERSION_PATCH}")
     message("wangshuqiang PROJECT_VERSION_TWEAK -> ${PROJECT_VERSION_TWEAK}")
     message("wangshuqiang CMAKE_PROJECT_VERSION -> ${CMAKE_PROJECT_VERSION}")

     # 运行结果
     wangshuqiang PROJECT_VERSION -> 3.2.1.2
     wangshuqiang PROJECT_VERSION_MAJOR -> 3
     wangshuqiang PROJECT_VERSION_MINOR -> 2
     wangshuqiang PROJECT_VERSION_PATCH -> 1
     wangshuqiang PROJECT_VERSION_TWEAK -> 2
     wangshuqiang CMAKE_PROJECT_VERSION -> 3.2.1.2
     ```

     ​	

3. 备注：

   1. project命令可以不行，cmake默认以"project"作为工程名，上述变量依旧被初始化
   2. project若被调用，需要在cmake_minimum_required命令调用之后，其他命令调用之前

**add_executable**命令解析

​	作用：通过指定的源文件列表构建出可执行目标文件,同样可以使用target_sources()命令继续为可执行目标文件添加源文件，前提是可执行目标文件已经被`add_executable`或`add_library`定义了。



### 2.通过配置文件添加宏定义(版本号、编译时间等)

#### 	1.cmake中设置的变量

```cmake
	# 版本号
	set(Launcher_VERSION_MAJOR 0)
	set(Launcher_VERSION_MINOR 1)
	# 编译时间
	string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")
```

#### 	2.创建并添加配置文件(xxx_config.h.in)

​		用户可通过在配置文件中编写相关内容，并调用`configure_file`命令，将输入文件中的内容复制替换到输出文件中，**注意：上文中的替换需要遵循一定的规则，是将输入文件中变量替换引用为@VAR@或${VAR}的变量值，如果未定义，则为空字符串**。

```cmake
# 输入文件
#define VERSION_MAJOR @Launcher_VERSION_MAJOR@
#define VERSION_MINOR @Launcher_VERSION_MINOR@

#define BUILD_TIMESTAMP "@BUILD_TIMESTAMP@"
```



#### 	3.调用configure_file命令，规定输入输出文件位置

​	`configure_file(<input> <output>)`

```cmake
configure_file("${PROJECT_SOURCE_DIR}/Config.h.in"
                "${PROJECT_SOURCE_DIR}/Config.h"
)
```

#### 	4.源文件中添加输出头文件即可引用

```C
#include "Config.h"
int main() {
  printf("wangshuqiang printf step1\r\n");
  printf("wangshuqiang printf VERSION_MAJOR_%d\r\n", VERSION_MAJOR);
  printf("wangshuqiang printf VERSION_MINOR%d\r\n", VERSION_MINOR);
  printf("wangshuqiang printf VERSION_PATCH%d\r\n", VERSION_PATCH);
  printf("wangshuqiang printf time stamp %s\r\n", "BUILD_TIMESTAMP");
  return 1;
}
```



## STEP2:添加一个库文件

​	**引言：实际开发过程中，经常会使用到库函数，可能是自己写的公共函数，可能是系统底层提供的公共接口，亦有可能时厂家提供的三方接口，如何让这些库函数参与编译就是STEP2需要研究的问题**

### 	1.创建子文件夹，同时在子文件夹内创建CMakeLists.txt文件

#### 			1.在子文件夹中的CMakeLists.txt文件中调用`add_library`命令。

​		`add_library命令解析`：

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

​			该命令用来是 CMake 中用于创建**库目标**的命令。库目标可以是静态库、共享库或模块库。

​			中间的选项可以用来选择生成静态库、动态库、模块库

​			注：库目标的名称必须在项目范围内唯一

#### 			2.创建源文件、头文件并编写库函数

### 	2.在顶层CMakeLists.txt文件添加库

#### 		1.调用`add_subdirectory`命令添加文件夹

​	命令作用：**添加一个子目录并构建该子目录**

注1：当调用**add_subdirectory**命令后，cmake构建工程会自动将该子目录添加到编译和链接的搜索目录中，以保证整个构建工程能满足依赖，这也是为什么使用add_subdirectory后不需要将子文件夹加入到头文件或库文件搜索目录也能搜索到子目录的头文件或库文件。

注2：该命令**不得**使用set变量方式进行引用如：

```cmake
# 错误示范 如果这么写，只会运行A目录下的CMakeLists.txt,B/C下的目录不会被执行
set(subdir A B C)
add_subdirectory(${subdir})
```



#### 		2.调用`target_link_libraries `命令



### 	3.进阶技巧：

#### 		库调用时可以设计成可选择模式，即当设置变量为ON时，使用该库函数，设置变量为OFF时，不使用该库函数

##### 			1.在CMakeLists.txt文件中，调用`option`命令设置变量的值

##### 			2.将CMakeLists.txt文件中国包括库函数的部分用宏包起来

##### 			3.通过STEP1中的configure_file命令，在输入文件中配置#cmakedefine

##### 			4.在源文件main中用宏将用到库函数的地方包起来		

