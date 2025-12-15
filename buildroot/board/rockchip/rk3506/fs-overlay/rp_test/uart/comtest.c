/*
 * MyCom.c                      //gcy
 */
#include <stdio.h>      // printf
#include <error.h>
#include <fcntl.h>      // open
#include <string.h>     // bzero
#include <stdlib.h>     // exit
#include <sys/times.h>  // times
#include <sys/types.h>  // pid_t
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <termios.h>    // termios, tcgetattr(), tcsetattr()
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>  // ioctl
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int convbaud(unsigned long int baudrate)
{
    switch (baudrate)
    {
        case 1200:
            return B1200;
        case 1800:
            return B1800;
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
        case 230400:
            return B230400;
        case 460800:
            return B460800;
        case 921600:
            return B921600;
        default:
            printf("不支持的波特率: %lu，使用默认值 115200\n", baudrate);
            return B115200;
    }
}

/*******************************************
 * Setup comm attr
 * fdcom: file descript
 * br: baudrate you want
 ********************************************/
int PortSet(int fdcom, unsigned long int br)
{
    struct termios termios_old, termios_new;
    int baudrate, tmp;
    char databit, stopbit, parity;

    bzero(&termios_old, sizeof(termios_old));
    bzero(&termios_new, sizeof(termios_new));
    cfmakeraw(&termios_new);
    tcgetattr(fdcom, &termios_old); // get the serial port attributions
    // baudrates
    baudrate = convbaud(br);
    cfsetispeed(&termios_new, baudrate);
    cfsetospeed(&termios_new, baudrate);
    termios_new.c_cflag |= (CLOCAL | CREAD);
    termios_new.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    termios_new.c_cflag &= ~CSIZE;
    databit = 8;
    switch (databit)
    {
        case '5':
            termios_new.c_cflag |= CS5;
            break;
        case '6':
            termios_new.c_cflag |= CS6;
            break;
        case '7':
            termios_new.c_cflag |= CS7;
            break;
        default:
            termios_new.c_cflag |= CS8;
    }

    parity = 0;
    switch (parity)
    {
        case '0':
            termios_new.c_cflag &= ~PARENB; // no parity check
            break;
        case '1':
            termios_new.c_cflag |= PARENB;  // odd check
            termios_new.c_cflag |= PARODD;
            break;
        case '2':
            termios_new.c_cflag |= PARENB;  // even check
            termios_new.c_cflag &= ~PARODD;
            break;
        case '3':
            termios_new.c_cflag &= ~PARENB; // space check
            break;
    }

    stopbit = '1';
    if (stopbit == '2')
    {
        termios_new.c_cflag |= CSTOPB;  // 2 stop bits
    }
    else
    {
        termios_new.c_cflag &= ~CSTOPB; // 1 stop bits
    }

    termios_new.c_oflag &= ~OPOST;
    termios_new.c_oflag &= ~(ONLCR | ICRNL);
    termios_new.c_iflag &= ~(ICRNL | INLCR);
    termios_new.c_iflag &= ~(IXON | IXOFF | IXANY);

    termios_new.c_cc[VMIN] = 0;
    termios_new.c_cc[VTIME] = 0;

    tcflush(fdcom, TCIFLUSH);
    tmp = tcsetattr(fdcom, TCSANOW, &termios_new);
    return (tmp);
}

/*******************************************
 * Open serial port
 * tty: 
 ********************************************/
int PortOpen(char *port)
{
    int fdcom;
    fdcom = open(port, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);
    return (fdcom);
}

/*******************************************
 * Close serial port
 ********************************************/
void PortClose(int fdcom)
{
    close(fdcom);
}

static int send_data = 0;
static int receive_data = 0;

int main(int argc, char *argv[])
{
    int fd;
    int var = 0;
    char buf[1024];
    int count;
    int i;
    unsigned long int baudrate = 115200; // 默认波特率 115200

    void funprint()
    {
        printf("com:%s, 发送数据量=%d\n", argv[1], send_data);
        printf("com:%s, 接收数据量=%d\n", argv[1], receive_data);
        exit(0);
    }

    signal(SIGTERM, funprint);

    if (argc < 2 || argc > 3)
    {
        printf("用法: comtest device_name [baudrate_or_selection]\n");
        printf("  baudrate_or_selection: 0-11 表示预定义波特率，或直接输入波特率值\n");
        printf("  预定义波特率: 0:1200, 1:1800, 2:2400, 3:4800, 4:9600, 5:19200,\n");
        printf("               6:38400, 7:57600, 8:115200, 9:230400, 10:460800, 11:921600\n");
        exit(1);
    }

    if (argc == 3)
    {
        char *endptr;
        long int value = strtol(argv[2], &endptr, 10);
        if (*endptr != '\0')
        {
            printf("无效的波特率参数: %s\n", argv[2]);
            exit(1);
        }
        if (value >= 0 && value <= 11)
        {
            static unsigned long int baudrates[] = {
                1200, 1800, 2400, 4800, 9600, 19200,
                38400, 57600, 115200, 230400, 460800, 921600
            };
            baudrate = baudrates[value];
            printf("使用预定义波特率 %lu (选择编号 %ld)\n", baudrate, value);
        }
        else if (value > 11)
        {
            baudrate = (unsigned long int)value;
            printf("使用直接输入的波特率 %lu\n", baudrate);
        }
        else
        {
            printf("无效的波特率值: %ld\n", value);
            exit(1);
        }
    }

    fd = PortOpen(argv[1]);
    if (fd == -1)
    {
        perror("端口打开错误:");
        exit(1);
    }
    else
    {
        printf("设备已打开，fd = %d\n", fd);
    }

    PortSet(fd, baudrate);
    while (1)
    {
        memset(buf, 0, 1024);
        count = read(fd, buf, 1024);
#if 1
        if (count != 0)
        {
            printf("接收到 %d 字节: ", count);
            for (i = 0; i < count; i++)
                printf("%c ", buf[i]);
            printf("\n");
        }
#endif
        var = ~var;
        if (var)
        {
            write(fd, "Send serial port odd!", 22);
        }
        else
        {
            write(fd, "Send serial port even! ", 23);
        }
        receive_data += count;
        send_data++;
        count = 0;
        usleep(115200 / baudrate * 250000);
    }
    return 0;
}
