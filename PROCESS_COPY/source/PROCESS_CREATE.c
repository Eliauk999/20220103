#include<PROCESS_COPY.h>
int PROCESS_CREATE(const char *Sfile,const char *Dfile,int prono,int blocksize){
    int pid;
    

    int flag;
    for(flag=0;flag<prono;flag++){
	pid=fork();
        if(pid==0)
            break;
    }
    if(pid>0){
        printf("parent process %d waiting  \n",getpid());
        PROCESS_WAIT();
    }else if (pid==0)
    {
        char STRPOS[100];
        char STRBLOCKSIZE[100];
        bzero(STRPOS,100);
        bzero(STRBLOCKSIZE,100);
        int POS;
	POS=flag*blocksize;
        sprintf(STRPOS,"%d",POS);
        sprintf(STRBLOCKSIZE,"%d",blocksize);
        printf("child process %d POS [%d] blocksize:%d\n",getpid(),POS,blocksize);

        execl("/home/roo/0103/PROCESS_COPY/module/COPY","COPY",Sfile,Dfile,STRPOS,STRBLOCKSIZE,NULL);
    }else{
        perror("fork call failed");
        exit(0);
    }
    return 0;

    }
    
