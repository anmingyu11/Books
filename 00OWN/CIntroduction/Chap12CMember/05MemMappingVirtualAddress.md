## 内存分页机制，完成虚拟地址的映射

关于虚拟地址和物理地址的映射有很多思路，我们可以假设以程序为单位，把一段与程序运行所需要的同等大小的虚拟空间映射到某段物理空间。

例如程序A需要 10MB 内存，虚拟地址的范围是从 0X00000000 到 0X00A00000，假设它被映射到一段同等大小的物理内存，地址范围从 0X00100000 到 0X00B00000，即虚拟空间中的每一个字节对应于物理空间中的每一个字节。

程序运行时，它们的对应关系如下图所示：

![](./05-01.jpg)

当程序A需要访问 0X00001000 时，系统会将这个虚拟地址转换成实际的物理地址 0X00101000，访问 0X002E0000 时，转换成 0X003E0000，以此类推。

这种以整个程序为单位的方法很好地解决了不同程序地址不隔离的问题，同时也能够在程序中使用固定的地址。

#### 地址隔离

如上图所示，程序A和程序B分别被映射到了两块不同的物理内存，它们之间没有任何重叠，如果程序A访问的虚拟地址超出了 0X00A00000 这个范围，系统就会判断这是一个非法的访问，拒绝这个请求，并将这个错误报告给用户，通常的做法就是强制关闭程序。

#### 程序可以使用固定的内存地址

虚拟内存无论被映射到物理内存的哪一个区域，对于程序员来说都是透明的，我们不需要关心物理地址的变化，只需要按照从地址 0X00000000 到 0X00A00000 来编写程序、放置变量即可，程序不再需要重定位。

#### 内存使用效率问题

以程序为单位对虚拟内存进行映射时，如果物理内存不足，被换入换出到磁盘的是整个程序，这样势必会导致大量的磁盘读写操作，严重影响运行速度，所以这种方法还是显得粗糙，粒度比较大。

### 内存分页机制

我们知道，当一个程序运行时，在某个时间段内，它只是频繁地用到了一小部分数据，也就是说，程序的很多数据其实在一个时间段内都不会被用到。

以整个程序为单位进行映射，不仅会将暂时用不到的数据从磁盘中读取到内存，也会将过多的数据一次性写入磁盘，这会严重降低程序的运行效率。

**现代计算机都使用分页（Paging）的方式对虚拟地址空间和物理地址空间进行分割和映射，以减小换入换出的粒度，提高程序运行效率。**

分页（Paging）的思想是指把地址空间人为地分成大小相等（并且固定）的若干份，这样的一份称为一页，就像一本书由很多页面组成，每个页面的大小相等。如此，就能够以页为单位对内存进行换入换出：

- 当程序运行时，只需要将必要的数据从磁盘读取到内存，暂时用不到的数据先留在磁盘中，什么时候用到什么时候读取。
- 当物理内存不足时，只需要将原来程序的部分数据写入磁盘，腾出足够的空间即可，不用把整个程序都写入磁盘。

#### 关于页的大小

页的大小是固定的，由硬件决定，或硬件支持多种大小的页，由操作系统选择决定页的大小。比如 Intel Pentium 系列处理器支持 4KB 或 4MB 的页大小，那么操作系统可以选择每页大小为 4KB，也可以选择每页大小为 4MB，但是在同一时刻只能选择一种大小，所以对整个系统来说，也就是固定大小的。

目前几乎所有PC上的操作系统都是用 4KB 大小的页。假设我们使用的PC机是32位的，那么虚拟地址空间总共有 4GB，按照 4KB 每页分的话，总共有 2^32 / 2^12 = 2^20 = 1M = 1048576 个页；物理内存也是同样的分法。

#### 根据页进行映射

下面我们通过一个简单的例子来说明虚拟地址是如何根据页来映射到物理地址的，请先看下图：

![](./05-02.jpg)

程序1和程序2的虚拟空间都有8个页，为了方便说明问题，我们假设每页大小为 1KB，那么虚拟地址空间就是 8KB。假设计算机有13条地址线，即拥有 2^13 的物理寻址能力，那么理论上物理空间可以多达 8KB。但是出于种种原因，购买内存的资金不够，只买得起 6KB 的内存，所以物理空间真正有效的只是前 6KB。

当我们把程序的虚拟空间按页分隔后，把常用的数据和代码页加载到内存中，把不常用的暂时留在磁盘中，当需要用到的时候再从磁盘中读取。上图中，我们假设有两个程序 Program 1 和 Program 2，它们的部分虚拟页面被映射到物理页面，比如 Program 1 的 VP0、VP1 和 VP7 分别被映射到 PP0、PP2 和 PP3；而有部分却留在磁盘中，比如 VP2、VP3 分别位于磁盘的 DP0、DP1中；另外还有一些页面如 VP4、VP5、VP6 可能尚未被用到或者访问到，它们暂时处于未使用状态。

> 这里，我们把虚拟空间的页叫做虚拟页（VP，Virtual Page），把物理内存中的页叫做物理页（PP，Physical Page），把磁盘中的页叫做磁盘页（DP，Disk Page）。

图中的线表示映射关系，可以看到，Program 1 和 Program 2 中的有些虚拟页被映射到同一个物理页，这样可以实现内存共享。

Program 1 的 VP2、VP3 不在内存中，但是当进程需要用到这两个页的时候，硬件会捕获到这个消息，就是所谓的页错误（Page Fault），然后操作系统接管进程，负责将 VP2 和 PV3 从磁盘中读取出来并且装入内存，然后将内存中的这两个页与 VP2、VP3 之间建立映射关系。