#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <string.h>

typedef struct cpu_occupy          //定义一个cpu occupy的结构体
{
    char name[20];                  //定义一个char类型的数组名name有20个元素
    unsigned int user;              //定义一个无符号的int类型的user
    unsigned int nice;              //定义一个无符号的int类型的nice
    unsigned int system;            //定义一个无符号的int类型的system
    unsigned int idle;              //定义一个无符号的int类型的idle
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
}cpu_occupy_t;

void cpu(char *str);
void mem(char *str);

void getResource(char *str)
{
    char mem_str[10];
    char cpu_str[10];
    mem(mem_str);
    cpu(cpu_str);
    sprintf(str, "-%s% -%s%", cpu_str, mem_str);
    //printf("%s", str);
}

double cal_cpuoccupy (cpu_occupy_t *o, cpu_occupy_t *n)
{
    double od, nd;
    double id, sd;
    double cpu_use ;

    od = (double) (o->user + o->nice + o->system +o->idle+o->softirq+o->iowait+o->irq);
    nd = (double) (n->user + n->nice + n->system +n->idle+n->softirq+n->iowait+n->irq);

    id = (double) (n->idle); 
    sd = (double) (o->idle) ;   
    if((nd-od) != 0)
        cpu_use =100.0 - ((id-sd))/(nd-od)*100.00; 
    else 
        cpu_use = 0;
    return cpu_use;
}

void get_cpuoccupy (cpu_occupy_t *cpust)
{
    FILE *fd;
    char buff[256];
    cpu_occupy_t *cpu_occupy;
    cpu_occupy=cpust;

    fd = fopen ("/proc/stat", "r");
    if(fd == NULL)
    {
        perror("fopen:");
        return;
    }
    fgets (buff, sizeof(buff), fd);

    sscanf (buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->system, &cpu_occupy->idle ,&cpu_occupy->iowait,&cpu_occupy->irq,&cpu_occupy->softirq);

    fclose(fd);
}

void cpu(char *str)
{
    cpu_occupy_t cpu_stat1;
    cpu_occupy_t cpu_stat2;
    double cpu;
	
    get_cpuoccupy((cpu_occupy_t *)&cpu_stat1);
	sleep(1);  //1s
    get_cpuoccupy((cpu_occupy_t *)&cpu_stat2);

    cpu = cal_cpuoccupy ((cpu_occupy_t *)&cpu_stat1, (cpu_occupy_t *)&cpu_stat2);

    sprintf(str, "%.2f", cpu);
}

void mem(char *str)
{
    struct sysinfo mem_info;
    sysinfo(&mem_info);
    sprintf(str, "%.2f", 100*((double)mem_info.totalram - (double)mem_info.freeram)/(double)mem_info.totalram);
}


