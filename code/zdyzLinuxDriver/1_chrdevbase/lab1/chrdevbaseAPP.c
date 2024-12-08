#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


/*
* argc: 应用程序参数个数
* argv[]: 具体的参数内容，字符串形式
* ./chrdevbaseAPP <filename>
*/
int main(int argc, char *argv[])
{
    int ret = 0;
    int fd = 0;
    char *filename;
    char readbuf[100], writebuf[100];

    filename = argv[1];

    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("Cann't open file %s\r\n", filename);
        return -1;
    }

    /* read */
    ret = read(fd, readbuf, 50);
    if(ret < 0) {
        printf("read file %s failed\r\n", filename);
    } else {

    }

    /* write */
    ret = write(fd, writebuf, 50);
    if(ret < 0){
        printf("write file %s failed\r\n", filename);
    } else {

    }

    /* close */
    ret = close(fd);
    if(ret < 0){
        printf("close file %s failed\r\n", filename);
    } 

    return 0;
}