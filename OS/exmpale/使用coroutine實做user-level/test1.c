#include <stdio.h>
#include <stdlib.h>     /* exit */
#include <setjmp.h>     /* jmp_buf, setjmp, longjmp */
#include <unistd.h>

static jmp_buf jmpbuf_th0;
static jmp_buf jmpbuf_th1;

static void thread_0() {
    printf("%s: 0\n", __FUNCTION__);
    sleep(1);
    longjmp(jmpbuf_th0, 1);
}

static void thread_1() {
    printf("%s: 0\n", __FUNCTION__);
    sleep(1);
    longjmp(jmpbuf_th1, 1);
}


int main() {
    int rc0, rc1;
// entry_thread_0:
    rc0 = setjmp(jmpbuf_th0);

    if (rc0 != 0) {
        thread_1();
    }

// entry_thread_1:
    rc1 = setjmp(jmpbuf_th1);
    thread_0();
    return 0;
}
