#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eth(char *str)
{
    FILE * fp;
    char buffer[2];
    char *eth_cmd = "cat /sys/class/net/en*/carrier";

    fp = popen(eth_cmd, "r");
    fgets(buffer, sizeof(buffer), fp);

    strcpy(str, buffer);

    pclose(fp);
}

void wifi(char *str)
{
    FILE * fp;
    char buffer[2];
    char *wifi_cmd = "cat /sys/class/net/wl*/carrier";

    fp = popen(wifi_cmd, "r");
    fgets(buffer, sizeof(buffer), fp);

    strcpy(str, buffer);

    pclose(fp);
}

void getNet(char *str)
{
    char eth_str[2];
    char wifi_str[2];

    eth(eth_str);
    wifi(wifi_str);

    if(eth_str[0] == '1')
    {
        strcpy(str, "eth-online");         
    }
    else
    {
        if(wifi_str[0] == '1')
        {
           strcpy(str, "wifi-online");
        }
        else
        {
            strcpy(str, "offline");
        }
    }    
}
