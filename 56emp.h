#ifndef __56EMP_H
#define __56EMP_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


typedef struct emp{
    int id;
    char name[20];
    double salary;
}EMP;
void writeemp();
void reademp();

#endif