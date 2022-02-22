#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getAlsa(char *str)
{
    FILE * fp;
    char buffer[3];
    
    //this cmd get sound
    char* cmd = "echo $(amixer get Master | tail -n1 | sed -r \"s/.*\\[(.*)%\\].*/\\1/\")";

    fp = popen(cmd, "r");
    fgets(buffer,sizeof(buffer),fp);

    sprintf(str, "%s%", buffer); 
    pclose(fp);
}
