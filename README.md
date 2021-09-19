# go-cqhttp-C
###### 编码原因目前还不支持使用中文，大概国庆会能够完善好
* 这是一个基于[go-cqhttp](https://github.com/Mrs4s/go-cqhttp)的C语言QQ机器人开源框架，大致可分为 API操作、
Event消息接收解析以及错误反馈。
> 制作这个的初衷是为了方便开发者能更加快捷的使用C语言制作出QQ机器人，
即使是对socket编程没有任何基础的编程小白也能在不具备socket相关知识
的情况下快速开发出机器人。

### 在使用此框架后，可以让开发QQ机器人的门槛下降一大截台阶，对于萌新十分友好，甚至可以拿来练练手，让自己有更多的开发经验。

***

因为本框架是基于go-cqhttp编写，所以在使用本框架时，需要同时本框架教学视频、
go-cqhttp开发文档以及本框架源代码中的注释。
本框架主要主要分为6个文件，分别为
### 实现go-cqhttp的API操作
* gocqhttp_API.h
* gocqhttp_API.c

### 实现go-cqhttp的事件接收
* gocqhttp_Event.h
* gocqhttp_Event.c

### 用于反馈go-cqhttp-C在使用时的错误
* gocqhttp_err.h
* gocqhttp_err.c

 ### 最后实在使用本开源框架时的注意事项
1.  如果没有十足的把握，请不要擅自修改框架的代码，否则很有可能会报错
2.  建议使用VS结合本框架来编写机器人
3.  如果在使用VS并结合本框架编写机器人，请进行以下设置：
> 打开菜单中的“项目”选项->选择当前项目的“项目属性”->
选择“C/C++”->找到“SDL检查”选项，将其改成“否”。
这样设置后便不会出现框架无法过编译的情况，但仍会出现
提示你将某些函数改成加了后缀"_s"的某些函数的Warning，
不理会即可
4. 如有遇到某些BUG，请加QQ群：721829413询问，这是使用go-cqhttp开发群器人的开发者交流群，go-cqhttp的开发者也在

如果遇到了某些go-cqhtpp的某些功能需要使用但本框架还未开发，请勿催促，
作者现在还是高中生，学校是月休，所以开发进度会有些慢，但还请耐心等待
