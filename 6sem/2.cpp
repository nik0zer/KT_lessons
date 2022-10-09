#include <stdio.h>
#include <pthread.h>

void a_f(void* arg)
{
    (*((int *)arg))++;
}

int main()
{
    int a = 0;
    size_t tr[5];
    pthread_create(tr, (pthread_attr_t *)NULL, (void* (*) (void*))a_f, &a);
    pthread_create(tr + 1, (pthread_attr_t *)NULL, (void* (*) (void*))a_f, &a);
    pthread_create(tr + 2, (pthread_attr_t *)NULL, (void* (*) (void*))a_f, &a);
    pthread_create(tr + 3, (pthread_attr_t *)NULL, (void* (*) (void*))a_f, &a);
    pthread_create(tr + 4, (pthread_attr_t *)NULL, (void* (*) (void*))a_f, &a);
    printf("%lu\n", tr[0]);
    printf("%lu\n", tr[1]);
    printf("%lu\n", tr[2]);
    printf("%lu\n", tr[3]);
    printf("%lu\n", tr[4]);
    printf("%lu\n", pthread_self());
    a++;
    pthread_join(tr[0], (void**) NULL);
    pthread_join(tr[1], (void**) NULL);
    pthread_join(tr[2], (void**) NULL);
    pthread_join(tr[3], (void**) NULL);
    pthread_join(tr[4], (void**) NULL);
    printf("%d", a);
}