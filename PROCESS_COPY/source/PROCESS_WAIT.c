#include<PROCESS_COPY.h>
int PROCESS_WAIT()
{
    int zpid;
    while ((zpid=wait(NULL))!=-1)
    {
        printf("wait zombie pid %d \n",zpid);
    }
    return 0;    
}
