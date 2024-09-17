#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
#include<string.h>
#include<sys/mman.h>

char * ptr = NULL;
struct pos
{
    int blocksize;
    int offset;
};


void * fun(void* arg){
    // sleep(1);
    struct pos *p=(struct pos*)arg;

    char buf[4096];
    bzero(buf,sizeof(buf));
    int blocksize=p->blocksize;
    int pos=p->offset;
    //输出到 buf 输出xx个字节， 以%s方式写入，起始+偏移位置
    // snprintf(buf,blocksize+1,"%s",ptr+pos);
    // printf("%s",buf);
    int fd=open("./3.jpg",O_RDWR|O_CREAT,0664);
    // lseek(fd,p->offset,SEEK_SET);
    // write(fd,buf,blocksize);

    // printf("%s\n",ptr);
    
    //讲数据复制到目标文件时，也要注意偏移量。
    // int fd=open("./dest",O_RDWR|O_CREAT,0664);
    lseek(fd,p->offset,SEEK_SET);
    write(fd,ptr+p->offset,p->blocksize);
    // pthread_exit(NULL);
    return 0;
}


int main() {
    int fd = open("./1.jpg",O_RDWR);
    if (fd<0)
    {
        perror("open:");
    }
    // lseek(fd,10,SEEK_END);
    // write(fd,"acd\n",4);
    int len = lseek(fd,0,SEEK_END);
    ptr = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (ptr==MAP_FAILED)
    {
        perror("MMAR\n:");
    }
    for (int i = 0; i < 4; i++)
    {   
        sleep(1);
        struct pos *p;
        p=(struct pos*)malloc(sizeof(p));
        p->blocksize=len/5;
        p->offset=i*p->blocksize;
        pthread_t tid;
        pthread_create(&tid,NULL,fun,(void*)p);
        pthread_join(tid,NULL);
    }
    


    // char * p;
    struct pos *p;
    p=(struct pos*)malloc(sizeof(p));
    p->blocksize=len/5;
    p->offset=p->blocksize*4;
    p->blocksize=len-p->offset;
    pthread_t tid;
    pthread_create(&tid,NULL,fun,(void*)p);
    pthread_join(tid,NULL);

    close(fd);

    int ret = munmap(ptr,len);
    if(ret == -1){
        perror("munmap\n");
    }    
    printf("done\n");
    return 0;
}