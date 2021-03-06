# UC-4.2

## 回顾

### Unix的内存管理--内存分配和回收的相关函数

1. malloc() and free()--- 分配多少，使用多少，释放多少
2. sbrk() and brk() --- sbrk()分配、brk()回收
3. mmap() and munmap()---mmap()内存映射、munmap()解除映射
4. void* sbrk(int)---int brk(void*)
5. void* mmap(void* addr,size_t size,int prot,int flags,int fd,off_t offset)
6. Unix的内核 通过 一系列系统函数（系统调用）与用户层保持联系

### Unix/Linux文件的读写操作（文件读写的系统调用）

### 文件描述符

1. 当系统打开一个文件时，会把文件的各种信息放入一段内存中，这段内存叫文件表，但文件表比较大，不利于传参等操作
2. 因此，文件表不对外提供，对外提供的是文件表的编号，这个编号叫文件描述符。文件描述符的本质就是一个非负整数，必须对应一张文件表才有效
3. 每个进程都有自己的文件描述符的总表，记录了文件描述符和文件表的对应关系
4. 0 1 2已经被系统预先使用，代表标准输入、标准输出和标准错误。文件描述符从3开始，最大到OPEN_MAX(Linux一般就是256个)
5. 文件描述符可以循环利用，close()以后就可以再次使用


### Linux系统中，文件的重要性

1. Linux中，几乎一切都可以看成文件。目录、内存、各硬件设备都可以看成文件
2. vim dir
3. /dec---硬件设备
4. /dec/tty--键盘，也是显示器
5. ls > /dec/tty---重定向到显示器
6. cat < /dev/tty---重定向到显示器
7. dec/null---空设备，就是用于清空东西的 虚拟设备
8. cat /dec/null > a.txt----清空a.txt的内容
9. ls -l >/dev/null---执行命令，但不做任何的显示
10. 在Linux系统中，对文件的操作非常重要，对文件的操作函数不止能操作文件，还能操作其他设备

### 常见的函数

1. open()---打开文件，返回文件描述符
2. close()---关闭文件
3. read()---读文件
4. write()---写文件
5. ioctl()---文件的控制函数（目前不讲）
6. 注：这5个函数不止操作文件，还能操作一些设备

### 实例

1. int open(char* filename,int flags,...)
	> 参数 filename 就是文件名（包括路径）
	> flags是打开的标识，主要包括：
		- O_RDONLY O_WRONLY O_RDWR:打开的权限，三个必选其一
		- O_CREAT -创建标记，文件存在就打开，不存在就新建；
		- -O_TRUNC:打开文件时自动清空（open()是清空）
		- -O_EXCL:文件不存在新建，存在就返回-1代表出错
		- 上面两个一般都是和O_CREAT结合使用
		- O_APPEND:采用追加的方式文件，一般用于写
		- 参数...代表0-n个任意类型的参数，open()的第三个参数只在新建文件时有用，传入文件在硬盘上的权限
	> 返回文件描述符，失败返回-1
	> 注：文件权限和打开权限不同，打开权限是文件权限的子集，文件在硬盘上的权限与程序无关，程序的权限是打开权限
	> 权限都是8进制，8进制和16进制都是2进制的简写，8进制是3位二进制简写成一位8进制，16进制是4位二进制简写为一位16

2. int read(int fd,void* buf,size_t count)
3. int write(int fd,void* buf,size_t length)
	> 参数fd就是文件描述符，可以通过open()获得
	> buf就是读/写的内存的首地址，一般都是变量的地址
	> 参数count是buf的真实大小，不一定读满
	> 参数length不是buf的大小，而是写入数据的大小（写满）
	> read()返回正数就是真实读到的字节数，0：读完；-1：出错；
	> write()返回正数就是真实写入的字节数，0代表什么都没写，-1代表出错
4. 系统有一个权限屏蔽字，默认权限屏蔽是屏蔽用户的写权限，权限屏蔽字可以修改



















