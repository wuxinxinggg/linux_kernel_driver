#include <stdio.h>
#include <unistd.h>

#define THREAD_INTERVAL 500
#define cr_start() \
        static int __s = 0; \
        switch (__s) { \
          case 0:
#define cr_yield \
          { __s = __LINE__; \
            usleep(THREAD_INTERVAL); \
            return; \
          case __LINE__: ; \
          }
#define cr_end() \
        } __s = 0;

static int condition = 1;

static void user_thread_1() {
    cr_start();

    for (; ;) {
        /* do something */
        printf("Run %s\n", __FUNCTION__);
        cr_yield;
    }

    cr_end();
}

static void user_thread_2() {
    cr_start();

    for (; ;) {
        if (condition) {
            /* do something conditional */
            printf("Run %s - (1)\n", __FUNCTION__);
            cr_yield;
        }

        /* do something */
        printf("Run %s - (2)\n", __FUNCTION__);
        condition = !condition;
        cr_yield;
    }

    cr_end();
}

int main() {
    for (; ;) {
        user_thread_1();
        user_thread_2();
    }

    return 0;
}
