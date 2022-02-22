#include <stdio.h>
#include <time.h>
#include <string.h>

void getDate(char *str)
{
    char *arr[] = {"日", "一", "二", "三", "四", "五", "六"};

    time_t t;
    struct tm * lt;
    struct tm info;

    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    
    //星期几
    memset(&info, 0, sizeof(info));
    info.tm_year = lt->tm_year;
    info.tm_mon = lt->tm_mon;
    info.tm_mday = lt->tm_mday;
    mktime(&info);

    sprintf(str, " %s %d/%d/%d %d:%d:%d", arr[info.tm_wday], lt->tm_year+1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
}
