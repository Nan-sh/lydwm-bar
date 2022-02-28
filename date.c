#include <stdio.h>
#include <time.h>
#include <string.h>

void getDate(char *str)
{
    char *arr[] = {"日", "一", "二", "三", "四", "五", "六"};
    char hour[4];
    char min[4];
    char sec[4];

    memset(hour, 0, 4);
    memset(min, 0, 4);
    memset(sec, 0, 4);

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

    if(lt->tm_hour < 10)
    {
	sprintf(hour, "0%d", lt->tm_hour);
    }
    else
	sprintf(hour, "%d", lt->tm_hour);    

    if(lt->tm_min < 10)
    {
	sprintf(min, "0%d", lt->tm_min);
    }
    else
	sprintf(min, "%d", lt->tm_min);

    if(lt->tm_sec < 10)
    {
	sprintf(sec, "0%d", lt->tm_sec);
    }
    else
	sprintf(sec, "%d", lt->tm_sec);

    sprintf(str, " %s %d/%d/%d %s:%s:%s", arr[info.tm_wday], lt->tm_year+1900, lt->tm_mon + 1, lt->tm_mday, hour, min, sec);//输出结果
}
