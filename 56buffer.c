#include"56emp.h"
//标C和UC在数据处理的区别
int i;
//标c有系统提供的缓冲区
void Std_C(){
    FILE* file = fopen("stdc.tex","w");
    if(file == NULL){
        perror("fopen");
        exit(-1);
    }
    
    for(i=0;i<1000000;++i){
        fwrite(&i,sizeof(int),1,file);
    }
    fclose(file);
}
//UC没有缓冲区，写一次就要访问一次内核
void UC(){
    int fd = open("uc.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd == -1){
        perror("open");
        exit(-1);
    }
    for(i=0;i<1000000;++i){
        write(fd,&i,sizeof(int));
    }
    close(fd);

}
//程序员可以自己加buffer
void UC_buffer(){
    int fd = open("uc_buffer.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd == -1){
        perror("open");
        exit(-1);
    }
    int arr[10000]={};
    for(i=0;i<1000000;++i){
        arr[i%10000]=i;    //i%10000:0-9999
        if(i%10000==9999)  //满缓冲区才写
        write(fd,arr,sizeof(arr));
    }
    close(fd);

}
int main(){
    //Std_C();
    UC();
    //UC_buffer();
    return 0;
}