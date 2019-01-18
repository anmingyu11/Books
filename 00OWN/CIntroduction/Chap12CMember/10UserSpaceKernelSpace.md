## 用户模式和内核模式

首先我们要解释一个概念——进程（Process）。简单来说，一个可执行程序就是一个进程，前面我们使用C语言编译生成的程序，运行后就是一个进程。进程最显著的特点就是拥有独立的地址空间。

**严格来说，程序是存储在磁盘上的一个文件，是指令和数据的集合，是一个静态的概念；进程是程序加载到内存运行后一些列的活动，是一个动态的概念。**

前面我们在讲解地址空间时，一直说“程序的地址空间”，这其实是不严谨的，应该说“进程的地址空间”。一个进程对应一个地址空间，而一个程序可能会创建多个进程。

### 内核模式和用户模式