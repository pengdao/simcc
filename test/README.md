### unittest

#### test_01

测试std::shared_ptr的reset 接口释放所拥有对象的管理权功能。

```c++
std::shared_ptr<classA>	msg_ptr (new classA());   //msg_ptr 拥有一个classA对象的管理权
msg_ptr.reset(new classA());  //msg_ptr 释放掉前一个对象的管理权，管理新对象
```

#### test_pattern_proxy

设计模式之代理模式用例

