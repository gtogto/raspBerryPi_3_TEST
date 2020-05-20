#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main()
{
    int fd;
    int data;

    if ((fd == serialOpen ("/dev/ttyAMA0", 115200)) < 0)
    {
        fprintf(stderr, "not Opened device : %s\n", strerror(errno));
        return 1;
    }

    printf("\n Raspberry Pi testing ... ");

    while(1)
    {
        data = serialGetchar(fd);
        printf("\nPC -> Rberry = %c", (char)data);
        serialPutchar(fd, data);
        serialPuts(fd, "\n");
        fflush(stdout);
    }

    return 0;
}
