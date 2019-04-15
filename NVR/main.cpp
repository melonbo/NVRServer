#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "ffmpeg/ffmpeg.h"
#include "live/proxy.h"

char url[1024];
pthread_t pid;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage: NVRServer rtsp://url\n");
        return 0;
    }
    printf("%s\n", argv[1]);
    sprintf(url, "%s", argv[1]);


    if(!pthread_create(&pid, NULL, proxyServer, NULL))
        printf("create proxy thread failed\n");

    FFMPEG stream;
    stream.initService();

    while(1)
    {
        printf("... ...");
        sleep(1);
    }
    return 0;
}

