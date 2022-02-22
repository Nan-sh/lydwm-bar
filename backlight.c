#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getBacklight(char *str)
{
    FILE *cur_backlight_file;
    FILE *max_backlight_file;

    int cur;
    int max;
    char buf[10];

    memset(buf, 0, 10);
    cur_backlight_file = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
    if(cur_backlight_file == NULL)
    {
        perror("fopen:");
        return;
    }
    fgets(buf, sizeof(buf), cur_backlight_file);
    cur = strtol(buf, NULL, 10);
    fclose(cur_backlight_file);

    memset(buf, 0, 10);
    max_backlight_file = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
    if(max_backlight_file == NULL)
    {
        perror("fopen:");
        return;
    }
    fgets(buf, sizeof(buf), max_backlight_file);
    max = strtol(buf, NULL, 10);
    fclose(max_backlight_file);
    
    sprintf(str, "%d", 100 * cur/max);
}
