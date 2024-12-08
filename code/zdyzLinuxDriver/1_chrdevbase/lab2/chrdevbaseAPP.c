#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


/*
* argc: 应用程序参数个数
* argv[]: 具体的参数内容，字符串形式
* ./chrdevbaseAPP <filename> <1:2> 1表示读，2表示写
* ./chrdevbaseAPP /dev/chrdevbase 1 表示从驱动里面读数据
* ./chrdevbaseAPP /dev/chrdevbase 2 表示向驱动里面写数据
*/
int main(int argc, char *argv[])
{
    int ret = 0;
    int fd = 0;
    char *filename;
    char readbuf[100], writebuf[100];
    static char usrdata[] = {"usr data"};

    if(argc != 3) {
        printf("Error usage!\r\n");
        return -1;
    }

    filename = argv[1];

    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("Cann't open file %s\r\n", filename);
        return -1;
    }

    /* read */
    if(atoi(argv[2] == 1)) { /* 读 */
        ret = read(fd, readbuf, 50);
        if(ret < 0) {
            printf("read file %s failed\r\n", filename);
        } else {
            printf("APP read data:%s\r\n", readbuf);
        }
    }

    /* write */
    if(atoi(argv[2] == 2)) { /* 写 */
        memcpy(writebuf, usrdata, sizeof(usrdata));
        ret = write(fd, writebuf, 50);
        if(ret < 0){
            printf("write file %s failed\r\n", filename);
        } else {
            // printf("APP write data\r\n");
        }
    }

    /* close */
    ret = close(fd);
    if(ret < 0){
        printf("close file %s failed\r\n", filename);
    } 

    return 0;
}