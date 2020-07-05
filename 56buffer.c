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
