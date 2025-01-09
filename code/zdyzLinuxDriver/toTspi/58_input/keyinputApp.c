#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

/*
* 描述  : input 子系统测试APP
*/

/* 定义一个input_event变量, 存放输入事件信息 */
static struct input_event inputevent;


/*
* @description  : main 主程序
* @param - argc : argv 数组元素个数
* @param - argv : 具体参数
* @return       : 0 成功; 其他 失败
*/
int main(int argc, char *argv[])
{
    int fd;
    int err = 0;
    char *filename;

    filename = argv[1];

    if(argc != 2) {
        printf("Error Usage!\r\n");
        return -1;
    }

    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("Can't open file %s\r\n", filename);
        return -1;
    }

    while(1) {
        err = read(fd, &inputevent, sizeof(inputevent));
        if(err > 0) { //读取数据成功
            switch(inputevent.type) {
                case EV_KEY:
                    if(inputevent.code < BTN_MISC) {  // 键盘键值
                        printf("key %d %s\r\n", inputevent.code,
                                inputevent.value ? "press" : "release");
                    } else {
                        printf("button %d %s\r\n", inputevent.code,
                                inputevent.value ? "press" : "release");
                    }
                    break;
                
                /* 其他类型的事件，自行处理 */
                case EV_REL:
                    break;
                case EV_ABS:
                    break;
                case EV_MSC:
                    break;
                case EV_SW:
                    break;
            } 
        } else {
            printf("读取数据失败\r\n");
        }
    }
    return 0;
}