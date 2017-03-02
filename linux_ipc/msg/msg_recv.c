#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSG_SIZE 128

typedef struct message_buf_s {
    long mtype;
    char mtext[MSG_SIZE];
} message_buf_t;


int main()
{

    int msg_id;
    key_t key;
    message_buf_t rbuf;
    int ret = -1;

    key = 1234;
    msg_id =  msgget(key, 0666);
    if(msg_id < 0) {
        perror("msgget");
        exit(1);
    }
    ret = msgrcv(msg_id, &rbuf, MSG_SIZE, 1, 0);
    if(ret < 0) {
        perror("msgrcv");
        exit(1);
    }
    printf("recv: %s\n", rbuf.mtext);
    return 0;
}
