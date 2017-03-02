#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSG_SIZE 128
typedef struct message_buf_s {
    long mtype;
    char mtext[MSG_SIZE];
} message_buf_t;

int main(int argc, char **argv)
{
    int msg_id;
    int msg_flg = IPC_CREAT | 0666;
    key_t key;
    message_buf_t sbuf;
    unsigned int buf_len;
    int ret = -1;

    key = 1234;

    msg_id = msgget(key, msg_flg);
    if(msg_id < 0) {
        perror("msgget");
        exit(1);
    }

    sbuf.mtype = 1;
    memcpy(sbuf.mtext, "hello", 6);
    buf_len = 6;

    ret = msgsnd(msg_id, &sbuf, buf_len, IPC_NOWAIT);
    if(ret < 0) {
        perror("msgsnd");
        exit(1);
    }
    else {
        printf("Message sent: %s\n", sbuf.mtext);
    }
    return 0;
}
