#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include "config.h"

static Display *dpy;

void setstatus(char *str)
{
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}

int main()
{
    char *resource; 
    char *battery; 
    char *date;    
    char *backlight; 
    char *alsa;
    char *network;
    char *status;

    if(!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

    while(1)
    {
        resource = (char *)malloc(sizeof(char) * 50);
        battery = (char *)malloc(sizeof(char) * 10);
        date = (char *)malloc(sizeof(char) * 30);
        backlight = (char *)malloc(sizeof(char) * 10);
        alsa = (char *)malloc(sizeof(char) * 10);
        network = (char *)malloc(sizeof(char) * 20);
        status = (char *)malloc(sizeof(char) * 150);

        getResource(resource);
        getBattery(battery);
        getDate(date);
        getBacklight(backlight);
        getAlsa(alsa);
        getNet(network);

        sprintf(status, "[] [%s] [%s] [-%s%] [-%s%] [ %s] [%s]", resource, battery, backlight, alsa, network, date);
        printf("%s\n", status);
        setstatus(status);

        free(resource);
        free(battery);
        free(date);
        free(backlight);
        free(alsa);
        free(network);
        free(status);

        sleep(1);
    }
    
    XCloseDisplay(dpy);
	return 0;
}
