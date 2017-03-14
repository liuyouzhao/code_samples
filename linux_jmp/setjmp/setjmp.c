#include <stdio.h>
#include <setjmp.h>

static jmp_buf jbuf_sched;
static jmp_buf jbuf_thread1;
static jmp_buf jbuf_thread2;

static jmp_buf *pcur_thread;

#define __SET_JMP(jbuf) \
              setjmp(jbuf); \
              pcur_thread = &jbuf;

int thread1()
{
    int i = 0;
    int n = -1;
    int p = 1;
    while(1) {
        /* thread behaviors */
        printf("thread1 done! %d %d\n", n, p);
        n ++;
        p = -p;
        i = __SET_JMP(jbuf_thread1);
        if(i == 0 && n == 0) {
            printf("thread1 created!\n");
            return 0;
        }
        else if(i == 1) {
            printf("thread1 brougt up again\n");
            continue;
        }
        else if(n == 0) {
            perror("thread1");
            return -1;
        }
        printf("thread1 suspend:%d\n", i);
        longjmp(jbuf_sched, 0);
    }
}

int thread2()
{
    int i = 0;
    int m = -1;
    while(1) {
        /* thread behaviors */
        printf("thread2 done! %d %d\n", m, i);
        m ++;
        i = __SET_JMP(jbuf_thread2);
        if(i == 0 && m == 0) {
            printf("thread2 created!\n");
            return 0;
        }
        else if(i == 1) {
            printf("thread2 brougt up again\n");
            continue;
        }
        else if(m == 0) {
            perror("thread2");
            return -1;
        }

        printf("thread2 suspend:%d\n", i);
        longjmp(jbuf_sched, 0);
    }
}

#if DEBUG
#define __SCHED_BEGIN__(i) \
        printf("\n__SCHED_BEGIN__ %d\n", i);
#define __SCHED_END__ \
        printf("\n__SCHED_END__\n");
#else
#define __SCHED_BEGIN__(i)
#define __SCHED_END__
#endif

int schedule()
{
    int i = 0;
    i = setjmp(jbuf_sched);
    __SCHED_BEGIN__(i);
    switch(i) {
    case 0:
    case 1:
        if(pcur_thread == &jbuf_thread1) {
            pcur_thread = &jbuf_thread2;
            __SCHED_END__
            longjmp(jbuf_thread2, 0);
        }
        else if(pcur_thread == &jbuf_thread2) {
            pcur_thread = &jbuf_thread1;
            __SCHED_END__
            longjmp(jbuf_thread1, 0);
        }
        else {
            pcur_thread = &jbuf_thread1;
            __SCHED_END__
            longjmp(jbuf_thread1, 0);
        }
    break;
    default:
        printf("schedule error: %d\n", i);
    break;
    }

}


int main()
{
    thread1();
    thread2();
    schedule();
    return 0;
}
