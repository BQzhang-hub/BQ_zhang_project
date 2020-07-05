# UC-3.13

## 回顾

1. gcc的用法（不常用的百度）
2. 预处理的指令
3. 环境变量
4. 头文件的编写和使用
5. 相对路径的可移植性强

## 静态库和共享库

1. 库文件就是程序的打包，Unix和Windows中都使用了库文件，库文件分为：静态库和共享库（动态库）
2. 静态库是代码的归档，每次使用时都会直接复制代码段到目标文件中
3. 共享库是代码的集合，每次使用时都不复制代码段，而是提供代码的地址（函数指针）
4. 静态库的优缺点：
	> 速度稍快
	> 连接成功后与库文件完全脱离。
	> 占用空间非常大，而且不利于修改和维护
5. 共享库的优缺点：
	> 占用空间小，修改和维护比较方便
	> 速度稍慢，连接成功后 目标文件和共享库文件必须存在才可以运行代码
6. 开发项目时，绝大数使用共享库。因此，C程序员需要提供两样东西：共享库文件和头文件
----
7. 创建静态库和使用
	> 写源程序，保存退出
	> 编译源程序为.o文件，gcc -c add.c
	> 把所有.o文件打包成静态库文件（lib库名.a）
	> ar -r libmylib.a add.o
8. 静态库的使用
	> 写调用的代码，保存退出。
	> 编译调用代码.o文件，gcc -c test.c
	> 连接调用程序和静态库文件
```
1. 直接连接法
	gcc test.o libmyku.a
2. 双L连接法（库名不带lib和.a）
	gcc test.o -l库名 -L库所在的目录
3. 但l连接法
	首先配置环境变量LIBRATY_PATH,把库所在的目录配置进来
	gcc test.o -l库名

```

9. gcc -static ---静态编译
	
----

10. 创建共享库
	> 写源程序，程序退出
	> 编译生成共享库文件
      - gcc -fpic -shared add.c -o libmyku.so(-fpic可省略)  
11. 使用共享库
	> 与静态库的三种方式一样
	> 注：共享库在运行期间需要配置环境变量
	> LD_LIBRARY_PATH为共享库的目录
	> ldd a.out--查看关联的共享库文件
	> 重启后环境不行
12. 其实就是想stdio一样，将自己的源文件制作成库，然后main()调用
13. 静态库和动态库可以使一大堆.O文件变成一个lib

----
14. 系统提供了直接打开共享库的函数
15. #include<dlfcn.h>
16. dlopen()--打开一个共享库文件
17. dlsym()--从一个打开的共享库文件中找到一个函数
18. dlclose()--关闭打开的文件
19. dlerror()--处理上面三个函数产生的错误
20. （了解即可，动态编程）

----
	
## C程序员的错误处理

1. 错误处理解决不了所有的问题，只是在可控的范围内，对错误的情况进行编码处理
2. 错误处理对于所有的语言都是必须的，后期的语言都使用异常机制 进行错误处理
3. C程序没有异常机制，有返回值 标识错误，判断返回值进行错误的处理
4. 返回标识错误的4种情况：
	> 1. 若函数返回值是int，并且返回的数据不可能是负数；直接返回-1代表出错，非负数代表正数代表正常返回的数据
	> 2. 若函数返回值是int,但返回的数据也可以是负数；返回0代表正常，返回-1代表出错。用指针类型的参数带出返回的数据
	> 3. 若函数返回值是指针，返回NULL代表出错，其他情况代表正常的返回指针
	> 4. 若函数不需要考虑出错的情况，可以void返回值
	> 注：以上4种不是绝对的，只是经验的总结。
```
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


int suijishu(){  //产生随机数
        srand(time(NULL));
        int i = rand() % 10 + 1;
        if(i == 5)
                return -1;
        else
                return i;
}

int max(int a,int b,int * pi){
        if(a>b||a<b){

                *pi = (a>b) ? a:b;
                return 0;
        }
        else
                return -1;

}

char* cs(char* s){
        //s是字符串，*s是对应地址的字符
        //if(s == "error" 
        )//y语法正确，比较的是字符串的地址
        if(!strcmp(s,"error"))//
                return NULL;
        else
                return s;

}

void print_s(const char* s){
        prinft("\n");

                printf("%s\n");
}
int main(void){
        int b = suanjishu();
        if(b == -1)
                printf("error\n");
        else
                printf("%d\n",b);
        int ma = 0;
        b = max(-1,-2,&ma);//ma存储最大值
        char* s1=cs("error");
}
```

----

5. C标准中，对于错误处理提供了1个全局变量和3个函数
6. errno--外部的全部变量，用于存储错误的编号
7. 函数：strrror();perror();printf()都可以把错误的编号变成错误的信息
	> strerror()--传入一个错误编号，返回错误信息
	- perror()-打印当前的错误信息（自动查找errno得到错误编号）
	- printf("%m")-打印当前的错误信息（自动查找errno）
8. errno的值在调用函数时，出错就会改变；但是调用函数时，不出错，errno的值不变。
9. 不能errno判断某个函数是不是出错，只能通过函数的返回值判断是否出错。
10. eerno的作用是出了错以后，获得具体的错误信息
11. 注：errno不是所有函数都使用，某些函数没有使用（线程）

----

12. man 函数()----查看函数的RETURN　VAlUE是否用errno
13. man的作用
	> Unix/Linux命令
	- 函数
	- 头文件
14. man 2 mkdir---Linux手册

```
#include<stdio.h>
#include<stdlib.h>
#include<error.h>

int main(void){
	FILE* file = fopen("/etc/passwd","r");
	if(file == NULL){
		printf("errno=%d\n",error);
		printf("fopen:%s\n",strerror(errno));
		perror("fopen");
		printf("%m\n");
	
	}
	else 
		printf("打开成功\n");
	if(file)         //更标准
		fclose(file);
	return 0;
}

```
15. 关于错误处理：用返回值表示是否出错，若出错了，找perrpr(),strerror();


## 环境变量和环境表

1. 环境变量表
	> C语言中，环境变量存在环境表中。环境表其实就是一个字符串的数组（字符指针数组）。char* arr[];//四字节
	- 大多数情况下，用char** 代表环境表
2. extren char** environ;//直接拿到环境表的首地址
```
#include<stdio.h>
#include<string.h>
int main(void){
	extren char** environ;//只需要获取不用赋值
	char** p = environ;//全局变量不要改变
	while(*p){//environ以NULL字符串结束
		p++;//r//内容上  char* 是四个字节
		*p++;//r//先p++
		** p++;//r//先p++
		(*p)++;//w//*p char移动1个字节
	}//练习：找到LANG的值，存入value中并打印出来
	p = environ;//回到初始位置
	char value[100] = {};//借助strncmp()比较部分字符串
	while(*p){//先保证整个字符集循环
		if(!strncmp(*p,"LANG=",5)){//4:error;5:right;*p：整个字符集进行比较
			strcpy(value,*p+5);
			break;
		}
		P++;
	}
	return 0;
}

```

3.

```
int * pi;
pi+1;//移动四个字节

char * pi;
pi+1;//移动一个字节

double * pi;
pi+1;//移动八个字节

//指针+1时，移动的字节数由sizeof(元素的类型)决定
```
----

4. 系统提供了关于环境变量和环境表的函数（熟悉）
>	
- getenv()---可以通过环境变量的名取得环境变量的值
- putenv()setenc()---可以新增/修改环境变量
- 区别在于putenv()存在必定修改，setenv()存在可选是否修改
- unsetenv()----单删某个环境变量
- clearenc()----全部删除环境变量
	
