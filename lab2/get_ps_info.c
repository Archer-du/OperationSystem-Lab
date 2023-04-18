#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<time.h>
#define MAX_PS_NUM 200
#define MAX_NAME_LEN 30
struct psinfo{
    pid_t pid;
    char *comm;
    volatile long stat;
    double cur_runtime;
    double prev_runtime;
    double CPU_usage;
} psinfo[MAX_PS_NUM];
int main(int argc, char *argv[]){
    int d;
    if(argc > 1){
        int d = atoi(argv[1]);
    }
    else d = 1;
    int num;
    char name[MAX_PS_NUM][MAX_NAME_LEN];
    pid_t pid[MAX_PS_NUM];
    volatile long stat[MAX_PS_NUM];
    unsigned long long cur_runtime[MAX_PS_NUM];
    int refreshtimes = 0;
    while(1){
        system("clear");
        syscall(332, &num, name, pid, stat, cur_runtime);
        for(int i = 0; i < num; i++){
            psinfo[i].prev_runtime = (refreshtimes == 0) ? (cur_runtime[i]/1000000000) : psinfo[i].cur_runtime;
            psinfo[i].pid = pid[i];
            psinfo[i].comm = name[i];
            psinfo[i].stat = stat[i];
            psinfo[i].cur_runtime = cur_runtime[i]/1000000000;
            psinfo[i].CPU_usage = (psinfo[i].cur_runtime - psinfo[i].prev_runtime)/d;
        }
        //排序
        struct psinfo tmp;
        for(int i = 0; i < num - 1; i++){
            for(int j = 0; j < num - 1 - i; j++){
                if(psinfo[j].CPU_usage < psinfo[j+1].CPU_usage){
                    tmp = psinfo[j+1];
                    psinfo[j+1] = psinfo[j];
                    psinfo[j] = tmp;
                }
            }
        }
        printf(" PID   COMM                                 STAT    %% CPU      TIME\n");
        for(int i = 0; i < 20; i++){
            printf(" %3d   %32s     %4ld    %5.1f      %-6.2f\n", psinfo[i].pid, psinfo[i].comm, psinfo[i].stat, psinfo[i].CPU_usage, psinfo[i].cur_runtime);
        }
        refreshtimes++;
        sleep(1);
    }
}